#include "SampleDesigner.h"
#include "DesignerScene.h"
#include "DesignerView.h"
#include "DesignerWidgetFactory.h"


SampleDesigner::SampleDesigner(QWidget *parent)
    : SampleDesignerInterface(parent)
    , m_widgetFactory(new DesignerWidgetFactory())
    , m_designerScene(0)
    , m_designerView(0)
//    , m_editorStack(0)
{
    m_designerScene = new DesignerScene(parent);
    m_designerView = new DesignerView(parent, m_designerScene);
//    m_editorStack = new QStackedWidget(parent);
//    m_editorStack->addWidget(m_designerView);
}


SampleDesigner::~SampleDesigner()
{
    delete m_widgetFactory;
}