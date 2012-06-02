#include "ToolData.h"

#include "PluginHub.h"
#include "PluginImageSettings.h"
#include "PluginPipeSettings.h"
#include "PluginTile.h"
#include "PluginImage.h"

#include <QDebug>
#include <QString>

ToolData::ToolData(PluginHub *hub)
    : ownerId(-1), groupId(-1), owner(""), group(""), m_hub(hub), m_enabledIds()
{
}

QList<PluginDependency*> ToolData::prerequisites(const PluginImageSettings &options, const PluginPipeSettings &settings) const {
    Q_UNUSED(options);
    Q_UNUSED(settings);
    QList<PluginDependency*> list;
    return list;
}

PluginData::Status ToolData::run(const PluginImageSettings &options, const PluginPipeSettings &settings)
{
	Q_UNUSED(options);
    Q_UNUSED(settings);

    qDebug() << "ToolData: run" << owner << "with id =" << ownerId << "data =" << this;

	return Complete;
}

bool ToolData::requiresDisk() const
{
	return false;
}

void ToolData::addEnabledId(int id) {
    m_enabledIds.append(id);
}
