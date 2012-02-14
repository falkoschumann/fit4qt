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

//#include <QtCore/QDebug>

namespace Fit {

TypeAdapter::TypeAdapter(const QMetaObject *metaObject, const QString name, bool isField) :
    m_metaObject(metaObject),
    m_name(name),
    m_field(isField)
{
}

bool TypeAdapter::isField() const
{
    return m_field;
}
bool TypeAdapter::isMethod() const
{
    return !isField();
}


// Factory //////////////////////////////////

TypeAdapter* TypeAdapter::createFieldAdapter(Fixture *fixture, const QString &fieldName)
{
    TypeAdapter * a = new TypeAdapter(fixture->metaObject(), fieldName, true);
    a->fixture = fixture;
    a->target = fixture;
    return a;
}

TypeAdapter* TypeAdapter::createMethodAdapter(Fixture *fixture, const QString &methodName)
{
    TypeAdapter * a = new TypeAdapter(fixture->metaObject(), methodName, false);
    a->fixture = fixture;
    a->target = fixture;
    return a;
}

// Accessors ////////////////////////////////

QVariant TypeAdapter::get()
{
    if (isField()) {
        int index = m_metaObject->indexOfProperty(m_name.toStdString().c_str());
        QMetaProperty field = m_metaObject->property(index);
        //qDebug() << "get" << field.name();
        return field.read(target);
    } else if (isMethod()) {
        QMetaMethod method;
        for (int i = 0; i < m_metaObject->methodCount(); ++i) {
            method = m_metaObject->method(i);
            if (QString(method.signature()).startsWith(m_name))
                break;
        }
        //qDebug() << "get" << method.signature();
        return invoke();
    }
    return QVariant();
}

void TypeAdapter::set(const QVariant &value)
{
    int index = m_metaObject->indexOfProperty(m_name.toStdString().c_str());
    QMetaProperty field = m_metaObject->property(index);
    bool ok = field.write(target, value);
    //qDebug() << "set" << field.name() << "to" << value << ok;
}

QVariant TypeAdapter::invoke()
{
    QMetaMethod method;
    for (int i = 0; i < m_metaObject->methodCount(); ++i) {
        method = m_metaObject->method(i);
        if (QString(method.signature()).startsWith(m_name))
            break;
    }
    QVariant result;
    bool ok;
    QString returnType(method.typeName());
    if (returnType == QString("int")) {
        int value;
        ok = method.invoke(target, Q_RETURN_ARG(int, value));
        result.setValue(value);
    } if (returnType == QString("float")) {
        float value;
        ok = method.invoke(target, Q_RETURN_ARG(float, value));
        result.setValue(value);
    }
    //qDebug() << "invoke" << method.signature() << ok << value;
    // return QVariant(QVariant::Int, &value);
    return result;
}

QVariant TypeAdapter::parse(const QString &s)
{
    int index = m_metaObject->indexOfProperty(m_name.toStdString().c_str());
    QMetaProperty field = m_metaObject->property(index);
    int type = field.type();
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
