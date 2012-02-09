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

#include "typeadapter.h"

namespace Fit {

TypeAdapter::TypeAdapter() :
    target(0),
    fixture(0)
{
}

// Factory //////////////////////////////////

TypeAdapter* TypeAdapter::on(Fixture *target, int type)
{
    TypeAdapter *a = adapterFor(type);
    a->init(target, type);
    return a;
}

TypeAdapter* TypeAdapter::on(Fixture *fixture, const QMetaProperty &field)
{
    TypeAdapter *a = on(fixture, field.type());
    a->target = fixture;
    a->field = field;
    return a;
}

TypeAdapter* TypeAdapter::on(Fixture *fixture, const QMetaMethod &method)
{
    TypeAdapter *a = on(fixture, method.methodType());
    a->target = fixture;
    a->method = method;
    return a;
}

TypeAdapter* TypeAdapter::adapterFor(int type)
{
    return new TypeAdapter();
}

// Accessors ////////////////////////////////

void TypeAdapter::init(Fixture *fixture, int type)
{
    this->fixture = fixture;
    this->type = type;
}

QVariant TypeAdapter::get()
{
    if (field.isValid())
        return field.read(target);
    //if (method)
        return invoke();
    return QVariant();
}

void TypeAdapter::set(const QVariant &value)
{
    field.write(target, value);
}

QVariant TypeAdapter::invoke()
{
    return method.invoke(target);
}

QVariant TypeAdapter::parse(const QString &s)
{
    return fixture->parse(s, type);
}

bool TypeAdapter::equals(const QVariant &a, const QVariant &b)
{
    if (a.isNull())
        return b.isNull();
    return a == b;
}

QString TypeAdapter::toString(const QVariant &o)
{
    if (o.isNull())
        return "null";
    return o.toString();
}

} // namespace Fit
