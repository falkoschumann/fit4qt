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

#include "fixtureregistry.h"
#include "parse.h"
#include "typeadapter.h"

#include <QtCore>

#include <stdexcept>

namespace Fit {

Fixture::RunTime::RunTime() :
    start(QDateTime::currentMSecsSinceEpoch()),
    elapsed(0)
{
}

QString Fixture::RunTime::toString()
{
    elapsed = QDateTime::currentMSecsSinceEpoch() - start;
    if (elapsed > 600000)
        return d(3600000) + ":" + d(600000) + d(60000) + ":" + d(10000) +d(1000);
    else
        return d(60000) + ":" + d(10000) + d(1000) + "." + d(100) + d(10);
}

QString Fixture::RunTime::d(long scale)
{
    long report = elapsed / scale;
    elapsed -= report * scale;
    return QString::number(report);
}

Fixture::Fixture(QObject *parent) :
    QObject(parent)
{
}

Fixture::~Fixture()
{
}

// Traversal //////////////////////////

void Fixture::doTables(Parse *tables)
{
    summary.insert("run date", QDateTime());
    QVariant runTime;
    runTime.setValue(RunTime());
    summary.insert("run elapsed time", runTime);
    if (tables) {
        Parse *fixtureName = getFixtureName(tables);
        if (fixtureName) {
            try {
                Fixture *fixture = getLinkedFixtureWithArgs(tables);
                fixture->interpretTables(tables);
            } catch (const std::exception &e) {
                exception(fixtureName, e);
                interpretFollowingTables(tables);
            }
        }
    }
}

void Fixture::interpretTables(Parse *tables)
{
    try { // Don't create the first fixture again, because creation may do something important.
        getArgsForTable(tables); // get them again for the new fixture object
        doTable(tables);
    } catch (const std::exception &ex) {
        exception(getFixtureName(tables), ex);
        return;
    }
    interpretFollowingTables(tables);
}

void Fixture::interpretFollowingTables(Parse *tables)
{
    //listener.tableFinished(tables);
    tables = tables->more;
    while (tables) {
        Parse *fixtureName = getFixtureName(tables);
        if (fixtureName) {
            try {
                Fixture *fixture = getLinkedFixtureWithArgs(tables);
                fixture->doTable(tables);
            } catch (const std::exception &e) {
                exception(fixtureName, e);
            }
        }
        //listener.tableFinished(tables);
        tables = tables->more;
    }
}

Fixture* Fixture::getLinkedFixtureWithArgs(Parse *tables)
{
    Parse *header = tables->at(0, 0, 0);
    Fixture *fixture = loadFixture(header->text());
    fixture->counts = counts;
    fixture->summary = summary;
    fixture->getArgsForTable(tables);
    return fixture;
}

Parse* Fixture::getFixtureName(Parse *tables)
{
    return tables->at(0, 0 ,0);
}

Fixture* Fixture::loadFixture(const QString &fixtureName)
{
    const QMetaObject *meta = FixtureRegistry::instance()->fixture(fixtureName);
    if (meta && meta->className() == fixtureName) {
        QObject *obj = meta->newInstance();
        if (!obj)
            throw std::runtime_error(QString("\"%1\" was found, but it's not a fixture.")
                                     .arg(fixtureName).toStdString());
        return qobject_cast<Fixture*>(obj);
    }

    throw std::runtime_error(QString("The fixture \"%1\" was not found.")
                             .arg(fixtureName).toStdString());
}

void Fixture::getArgsForTable(Parse *table)
{
    QStringList argumentList;
    Parse *parameters = table->parts->parts->more;
    for (; parameters ; parameters = parameters->more)
        argumentList.append(parameters->text());
    args = argumentList;
}

void Fixture::doTable(Parse *table)
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
    for (int i = 0; cells != 0; ++i) {
        try {
            doCell(cells, i);
        } catch (const std::exception &e) {
            exception(cells, e);
        }
        cells = cells->more;
    }
}

void Fixture::doCell(Parse *cell, int columnNumber)
{
    Q_UNUSED(columnNumber)
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

void Fixture::info(Parse *cell, const QString &message)
{
    cell->addToBody(info(message));
}

QString Fixture::info(const QString &message)
{
    return " <font color=\"#808080\">" + escape(message) + "</font>";
}

void Fixture::ignore(Parse *cell)
{
    cell->addToTag(" bgcolor=\"" + gray + "\"");
    counts.ignores++;
}

void Fixture::error(Parse *cell, const QString &message)
{
    cell->body = escape(cell->text());
    cell->addToBody("<hr><pre>" + escape(message) + "</pre>");
    cell->addToTag(" bgcolor=\"" + yellow + "\"");
    counts.exceptions++;
}

void Fixture::exception(Parse *cell, const std::exception &exception)
{
    QString message(exception.what());
    error(cell, message);
}

// Utility //////////////////////////////////

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

QString Fixture::camel(const QString &name)
{
    QStringList tokens(name.split(QRegExp("\\b")));
    if (tokens.size() <= 1)
        return name;
    QString result;
    foreach (QString token, tokens) {
        result += token.mid(0, 1).toUpper();
        result += token.mid(1);
    }
    return result;
}

QVariant Fixture::parse(const QString &s, int type)
{
    //return QVariant(type, &s);
    return QVariant::fromValue(s);
}

void Fixture::check(Parse *cell, TypeAdapter *a)
{
    QString text(cell->text());
    //qDebug() << "Fixture::check" << text;
    if (text.isEmpty()) {
        try {
            info(cell, a->toString(a->get()));
        } catch (const std::exception &e) {
            info(cell, "error");
        }
    } else if (!a) {
        ignore(cell);
    } else if (text == "error") {
        try {
            QVariant result(a->invoke());
            wrong(cell, a->toString(result));
        } catch (const std::exception &e) {
            right(cell);
        }
    } else {
        try {
            QVariant result(a->get());
            if (a->equals(a->parse(text), result))
                right(cell);
            else
                wrong(cell, a->toString(result));
        } catch (const std::exception &e){
            exception(cell, e);
        }
    }
}

} // namespace Fit
