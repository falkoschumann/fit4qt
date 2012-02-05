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

#include <fit/filerunner.h>
#include <fit/fixture.h>
#include <fit/parse.h>

#include <QtTest/QtTest>

using namespace Fit;

class FileRunnerTest : public QObject
{
    Q_OBJECT

private:
    void testHtml(const QString &html);

private slots:
    void testRunningFile();
    void testRunningFileWithWikiTag();
};

class TestFixture : public Fixture
{
    Q_OBJECT

public:
    Parse* tempParse;

    TestFixture(QObject *parent = 0) : Fixture(parent) {}
    ~TestFixture() {}
    void doTables(Parse *tables) { tempParse = tables; }
};

void FileRunnerTest::testRunningFile()
{
    QString simpleHtml =
            "<table>"
            "    <tr><td>fit.Fixture</td></tr>"
            "</table>";
    testHtml(simpleHtml);
}

void FileRunnerTest::testRunningFileWithWikiTag()
{
    QString wikiHtml =
            "<table><tr><td>extra formatting"
            "   <wiki>"
            "       <table>"
            "           <tr><td>fit.Fixture</td></tr>"
            "       </table>"
            "   </wiki>"
            "</td></tr></table>";
    testHtml(wikiHtml);
}

void FileRunnerTest::testHtml(const QString &html)
{
    TestFixture fixture;
    FileRunner runner;
    runner.fixture = &fixture;
    runner.input = html;
    QString s;
    runner.output.setString(&s);
    runner.process();

    QCOMPARE(fixture.tempParse->leaf()->text(), QString("fit.Fixture"));
}

QTEST_APPLESS_MAIN(FileRunnerTest)

#include "filerunnertest.moc"
