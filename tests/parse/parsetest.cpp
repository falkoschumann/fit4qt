/* Copyright (c) 2012; Falko Schumann, Muspellheim.de
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials  provided with the distribution.
 *  - Neither the name of the Muspellheim.de nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written  permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <fit/fitexcept.h>
#include <fit/parse.h>

#include <QtTest/QtTest>

using namespace Fit;

class ParseTest : public QObject
{
    Q_OBJECT

private slots:
    void testParsing();
    void testRecursing();
    void testIterating();
    void testIndexing();
    void testParseException();
    void testText();
    void testUnescape();
    void testWhitespaceIsCondensed();
};

void ParseTest::testParsing()
{
    QStringList tags;
    tags << "table";
    Parse p("leader<Table foo=2>body</table>trailer", tags);
    QCOMPARE(p.leader, QString("leader"));
    QCOMPARE(p.tag, QString("<Table foo=2>"));
    QCOMPARE(p.body, QString("body"));
    QCOMPARE(p.trailer, QString("trailer"));
}

void ParseTest::testRecursing()
{
    Parse p("leader<table><TR><Td>body</tD></TR></table>trailer");
    QCOMPARE(p.body, QString());
    QCOMPARE(p.parts->body, QString());
    QCOMPARE(p.parts->parts->body, QString("body"));
}

void ParseTest::testIterating()
{
    Parse p("leader<table><tr><td>one</td><td>two</td><td>three</td></tr></table>trailer");
    QCOMPARE(p.parts->parts->body, QString("one"));
    QCOMPARE(p.parts->parts->more->body, QString("two"));
    QCOMPARE(p.parts->parts->more->more->body, QString("three"));
}

void ParseTest::testIndexing()
{
    Parse p("leader<table><tr><td>one</td><td>two</td><td>three</td></tr><tr><td>four</td></tr></table>trailer");
    QCOMPARE(p.at(0,0,0)->body, QString("one"));
    QCOMPARE(p.at(0,0,1)->body, QString("two"));
    QCOMPARE(p.at(0,0,2)->body, QString("three"));
    QCOMPARE(p.at(0,0,3)->body, QString("three"));
    QCOMPARE(p.at(0,0,4)->body, QString("three"));
    QCOMPARE(p.at(0,1,0)->body, QString("four"));
    QCOMPARE(p.at(0,1,1)->body, QString("four"));
    QCOMPARE(p.at(0,2,0)->body, QString("four"));
    QCOMPARE(p.size(), 1);
    QCOMPARE(p.parts->size(), 2);
    QCOMPARE(p.parts->parts->size(), 3);
    QCOMPARE(p.leaf()->body, QString("one"));
    QCOMPARE(p.parts->last()->leaf()->body, QString("four"));
}

void ParseTest::testParseException()
{
    try {
        Parse p("leader<table><tr><th>one</th><th>two</th><th>three</th></tr><tr><td>four</td></tr></table>trailer");
    } catch (const Fit::parse_exception &e) {
        QCOMPARE(e.errorOffset(), 17);
        QCOMPARE(e.what(), "Can't find tag: td");
        return;
    }
    QFAIL("exptected exception not thrown");
}

void ParseTest::testText()
{
    QStringList tags;
    tags << "td";
    Parse p("<td>a&lt;b</td>", tags);
    QCOMPARE(p.body, QString("a&lt;b"));
    QCOMPARE(p.text(), QString("a<b"));
    p = Parse("<td>\ta&gt;b&nbsp;&amp;&nbsp;b>c &&&lt;</td>", tags);
    QCOMPARE(p.text(), QString("a>b & b>c &&<"));
    p = Parse("<td>\ta&gt;b&nbsp;&amp;&nbsp;b>c &&lt;</td>", tags);
    QCOMPARE(p.text(), QString("a>b & b>c &<"));
    p = Parse("<TD><P><FONT FACE=\"Arial\" SIZE=2>GroupTestFixture</FONT></TD>", tags);
    QCOMPARE(p.text(), QString("GroupTestFixture"));

    QCOMPARE(Parse::htmlToText("&nbsp;"), QString(""));
    QCOMPARE(Parse::htmlToText("a <tag /> b"), QString("a b"));
    QCOMPARE(Parse::htmlToText("a &nbsp;"), QString("a"));
    QCOMPARE(Parse::htmlToText("&amp;nbsp;"), QString("&nbsp;"));
    QCOMPARE(Parse::htmlToText("1 &nbsp; &nbsp; 2"), QString("1     2"));
    QString s("1 xxxx2");
    s[2] = QChar(0x00a0);
    s[3] = QChar(0x00a0);
    s[4] = QChar(0x00a0);
    s[5] = QChar(0x00a0);
    // FIXME: Repair test part
    //QCOMPARE(Parse::htmlToText(s), QString("1     2"));
    QCOMPARE(Parse::htmlToText("  <tag />a"), QString("a"));
    QCOMPARE(Parse::htmlToText("a<br />b"), QString("a\nb"));

    QCOMPARE(Parse::htmlToText("<font size=+1>a</font>b"), QString("ab"));
    QCOMPARE(Parse::htmlToText("a<font size=+1>b</font>"), QString("ab"));
    QCOMPARE(Parse::htmlToText("a<b"), QString("a<b"));

    QCOMPARE(Parse::htmlToText("a<br>b<br/>c<  br   /   >d"), QString("a\nb\nc\nd"));
    // FIXME: Repair test part
    //QCOMPARE(Parse::htmlToText("a</p><p>b"), QString("a\nb"));
    // FIXME: Repair test part
    //QCOMPARE(Parse::htmlToText("a< / p >   <   p  >b"), QString("a\nb"));
}

void ParseTest::testUnescape()
{
    QCOMPARE(Parse::unescape("a&lt;b"), QString("a<b"));
    QCOMPARE(Parse::unescape("a&gt;b&nbsp;&amp;&nbsp;b>c &&"), QString("a>b & b>c &&"));
    QCOMPARE(Parse::unescape("&amp;amp;&amp;amp;"), QString("&amp;&amp;"));
    QCOMPARE(Parse::unescape("a&gt;b&nbsp;&amp;&nbsp;b>c &&"), QString("a>b & b>c &&"));

    QString s;
    s.resize(3);
    s[0] = QChar(0x201c);
    s[1] = QChar(0x201d);
    s[2] = QChar(0x2019);
    QCOMPARE(Parse::unescape(s), QString("\"\"'"));
}

void ParseTest::testWhitespaceIsCondensed()
{
    QCOMPARE(Parse::condenseWhitespace(" a  b  "), QString("a b"));
    QCOMPARE(Parse::condenseWhitespace(" a  \n\tb  "), QString("a b"));
    QCOMPARE(Parse::condenseWhitespace(" "), QString());
    QCOMPARE(Parse::condenseWhitespace("  "), QString());
    QCOMPARE(Parse::condenseWhitespace("   "), QString());
    QCOMPARE(Parse::condenseWhitespace(QString(QChar((char) 160))), QString());
}

QTEST_APPLESS_MAIN(ParseTest)

#include "parsetest.moc"
