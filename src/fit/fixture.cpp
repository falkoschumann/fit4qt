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

#include "fixture.h"

#include "parse.h"

namespace Fit {

QString Fixture::label(const QString &string)
{
    return " <font size=-1 color=\"#c08080\"><i>" + string + "</i></font>";
}

QString Fixture::escape(const QString &string) {
    QString replaced(string);
    replaced.replace("&", "&amp;");
    replaced.replace("<", "&lt;");
    replaced.replace("  ", " &nbsp;");
    replaced.replace("\r\n", "<br />");
    replaced.replace("\r", "<br />");
    replaced.replace("\n", "<br />");
    return replaced;
}

Fixture::Fixture(QObject *parent) :
    QObject(parent)
{
}

// Traversal //////////////////////////

void Fixture::doTables(Parse *table)
{
    doRows(table->parts->more);
}

void Fixture::doRows(Parse *rows)
{
    while (rows) {
        Parse *more = rows->more;
        doRow(rows);
        rows = more;
    }
}

void Fixture::doRow(Parse *row)
{
    doCells(row->parts);
}

void Fixture::doCells(Parse *cells)
{
    for (int i = 0; cells; ++i) {
        //        try {
        doCell(cells, i);
        //        } catch (Exception e) {
        //            exception(cells, e);
        //        }
        cells = cells->more;
    }
}

void Fixture::doCell(Parse *cell, int columnNumber)
{
    ignore(cell);
}

// Annotation ///////////////////////////////

QString Fixture::green("#cfffcf");
QString Fixture::red("#ffcfcf");
QString Fixture::gray("#efefef");
QString Fixture::yellow("#ffffcf");

void Fixture::right(Parse *cell)
{
    cell->addToTag(" bgcolor=\"" + green + "\"");
    counts.right++;
}

void Fixture::wrong(Parse *cell)
{
    cell->addToTag(" bgcolor=\"" + red + "\"");
    cell->body = escape(cell->text());
    counts.wrong++;
}

void Fixture::wrong(Parse *cell, const QString &actual)
{
    wrong(cell);
    cell->addToBody(label("expected") + "<hr>" + escape(actual) + label("actual"));
}

void Fixture::ignore(Parse *cell)
{
    cell->addToTag(" bgcolor=\"" + gray + "\"");
    counts.ignores++;
}

} // namespace Fit
