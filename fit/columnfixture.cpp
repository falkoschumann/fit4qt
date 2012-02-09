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

#include "columnfixture.h"

#include "parse.h"
#include "typeadapter.h"

namespace Fit {

ColumnFixture::ColumnFixture(QObject *parent) :
    Fixture(parent),
    hasExecuted(false)
{
}

// Traversal ////////////////////////////////

void ColumnFixture::doRows(Parse *rows)
{
    bind(rows->parts);
    Fixture::doRows(rows->more);
}

void ColumnFixture::doRow(Parse *row)
{
    hasExecuted = false;
    try {
        reset();
        Fixture::doRow(row);
        if (!hasExecuted)
            execute();
    } catch (const std::exception &e) {
        exception(row->leaf(), e);
    }
}

void ColumnFixture::doCell(Parse *cell, int column)
{
    TypeAdapter *a = columnBindings[column];
    try {
        QString text(cell->text());
        if (text.isEmpty())
            check(cell, a);
        else if (!a)
            ignore(cell);
        else if (a->field.isValid())
            a->set(a->parse(text));
        else //if (a->method)
            check(cell, a);
    } catch (const std::exception e) {
        exception(cell, e);
    }
}

void ColumnFixture::check(Parse *cell, TypeAdapter *a)
{
    if (!hasExecuted) {
        try {
            execute();
        } catch (const std::exception e) {
            exception(cell, e);
        }
        hasExecuted = true;
        Fixture::check(cell, a);
    }
}

void ColumnFixture::reset()
{
    // about to process first cell of row
}

void ColumnFixture::execute()
{
    // about to process first method call of row
}

// Utility //////////////////////////////////

void ColumnFixture::bind(Parse *heads)
{
    columnBindings.clear();
    for (int i = 0; heads; heads = heads->more) {
        QString name(heads->text());
        QString suffix("()");
        try {
            if (name.isEmpty())
                columnBindings.insert(i, 0);
            else if (name.endsWith(suffix))
                columnBindings.insert(i, bindMethod(name.mid(0, name.length() - suffix.length())));
            else
                columnBindings.insert(i, bindField(name));
        } catch (const std::exception e) {
            exception(heads, e);
        }
    }
}

TypeAdapter* ColumnFixture::bindMethod(const QString &name)
{
    int index = targetClass()->indexOfSlot(camel(name).toStdString().c_str());
    return TypeAdapter::on(this, (targetClass()->method(index)));
}

TypeAdapter* ColumnFixture::bindField(const QString &name)
{
    int index = targetClass()->indexOfProperty(camel(name).toStdString().c_str());
    return TypeAdapter::on(this, (targetClass()->property(index)));
}

const QMetaObject* ColumnFixture::targetClass() const
{
    return metaObject();
}

} // namespace Fit
