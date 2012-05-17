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

#include "fixtureregistry.h"

#include "fitplugin.h"
#include "summary.h"
#include "utilities.h"

#include <QtCore>

namespace Fit {

FixtureRegistry::Manager FixtureRegistry::manager;

FixtureRegistry *FixtureRegistry::instance()
{
    if (!manager.instance)
        manager.instance = new FixtureRegistry();
    return manager.instance;
}

FixtureRegistry::FixtureRegistry()
{
    QMetaObject fixture = Summary::staticMetaObject;
    m_fixtures.insert(fixture.className(), &fixture);

    loadPlugins();
}

FixtureRegistry::~FixtureRegistry()
{
}

void FixtureRegistry::loadPlugins()
{
    QDir pluginsDir = directoryOf("plugins");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        if (FitPlugin *plugin = qobject_cast<FitPlugin *>(loader.instance())) {
            foreach (const QMetaObject *fixture, plugin->fixtures()) {
                m_fixtures.insert(fixture->className(), fixture);
            }
        }
    }
}

QList<const QMetaObject *> FixtureRegistry::fixtures() const
{
    return m_fixtures.values();
}

const QMetaObject *FixtureRegistry::fixture(const QString &fixtureName) const
{
    return m_fixtures.value(fixtureName);
}

} // namespace Fit
