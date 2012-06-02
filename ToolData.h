#ifndef TOOL_DATA_H
#define TOOL_DATA_H

#include "PluginData.h"

#include <QTime>

class ToolData : public PluginData
{

public:
    ToolData(PluginHub *hub);

    QList<PluginDependency*> prerequisites(const PluginImageSettings &options, const PluginPipeSettings &settings) const;
    Status run(const PluginImageSettings &options, const PluginPipeSettings &settings);
    bool requiresDisk() const;
    QString filterName() const { return ""; }

    int ownerId;
    int groupId;
    QString owner;
    QString group;

    void addEnabledId(int id);
    QList<int> *getEnabledIds() { return &m_enabledIds; }

private:
	PluginHub *m_hub;
    QList<int> m_enabledIds;
};

#endif
