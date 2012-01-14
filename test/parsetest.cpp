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

#include "parsetest.h"

#include <fit/parse.h>

#include <QtTest/QtTest>

namespace Fit4Qt {

ParseTest::ParseTest()
{
}

void ParseTest::testParsing()
{
    QStringList tags;
    tags << "table";
    Parse p("leader<Table foo=2>body</table>trailer", tags);
    QCOMPARE(QString("leader"), p.leader);
    QCOMPARE(QString("<Table foo=2>"), p.tag);
    QCOMPARE(QString("body"), p.body);
    QCOMPARE(QString("trailer"), p.trailer);
}

void ParseTest::testRecursing()
{
    Parse p("leader<table><TR><Td>body</tD></TR></table>trailer");
    QCOMPARE(QString(), p.body);
    QFAIL("not implemented yet");
    QCOMPARE(QString(), p.parts->body);
    QCOMPARE(QString("body"), p.parts->parts->body);
}

void ParseTest::testIterating()
{
    Parse p("leader<table><tr><td>one</td><td>two</td><td>three</td></tr></table>trailer");
    QFAIL("not implemented yet");
    QCOMPARE(QString("one"), p.parts->parts->body);
    QCOMPARE(QString("two"), p.parts->parts->more->body);
    QCOMPARE(QString("three"), p.parts->parts->more->more->body);
}

} // namespace Fit4Qt
