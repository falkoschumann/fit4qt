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

#ifndef FIT_FIXTURE_H
#define FIT_FIXTURE_H

#include "counts.h"

#include <QtCore/QHash>
#include <QtCore/QSet>
#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

#include <exception>

namespace Fit {

class Parse;
class TypeAdapter;

class Fixture : public QObject
{
    Q_OBJECT

public:
    static QSet<const QMetaObject*> fixtures;

    QHash<QString, QVariant> *summary;
    Counts *counts;

    class RunTime {
    public:
        long start;
        long elapsed;

        RunTime();
        QString toString();
        QString d(long scale);
    };

    Fixture(QObject *parent = 0);
    virtual ~Fixture();

    // Traversal
    virtual void doTables(Parse *tables);
    Parse* getFixtureName(Parse *tables);
    Fixture* loadFixture(const QString &getFixtureName);
    virtual void doTable(Parse *table);
    virtual void doRows(Parse *rows);
    virtual void doRow(Parse *row);
    virtual void doCells(Parse *cells);
    virtual void doCell(Parse *cell, int columnNumber);

     // Annotation
    static QString green;
    static QString red;
    static QString gray;
    static QString yellow;
    void right(Parse *cell);
    void wrong(Parse *cell);
    void wrong(Parse *cell, const QString &actual);
    void info(Parse *cell, const QString &message);
    QString info(const QString &message);
    void ignore(Parse *cell);
    void error(Parse *cell, const QString &message);
    void exception(Parse *cell, const std::exception &exception);

    // Utility
    static QString label(const QString &);
    static QString escape(const QString &);
    static QString camel(const QString &name);
    QVariant parse(const QString &s, int type);
    virtual void check(Parse *cell, TypeAdapter *a);

protected:
    QStringList args;

    // Traversal
    void interpretTables(Parse *tables);
    Fixture* getLinkedFixtureWithArgs(Parse *tables);
    void getArgsForTable(Parse *table);

private:
    // Traversal
    void interpretFollowingTables(Parse *tables);
};

} // namespace Fit

Q_DECLARE_METATYPE(Fit::Fixture::RunTime)

#endif // FIT_FIXTURE_H
