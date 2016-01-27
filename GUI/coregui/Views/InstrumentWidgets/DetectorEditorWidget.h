// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/DetectorEditorWidget.h
//! @brief     Defines class DetectorEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DETECTOREDITORWIDGET_H
#define DETECTOREDITORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class GroupBox;
class DetectorItem;
class AwesomePropertyEditor;
class QGridLayout;
class SphericalDetectorWidget;
class ColumnResizer;

class BA_CORE_API_ DetectorEditorWidget : public QWidget
{
    Q_OBJECT
public:
    DetectorEditorWidget(ColumnResizer *columnResizer, QWidget *parent = 0);
    virtual ~DetectorEditorWidget();

    void setDetectorItem(DetectorItem *detectorItem);

signals:
    void extendedDetectorEditorRequest(DetectorItem *);

public slots:
    void onPropertyChanged(const QString &propertyName);
    void onSubItemChanged(const QString &propertyName);
    void onSubItemPropertyChanged(const QString &property_group, const QString &property_name);

private slots:
    void onGroupBoxExtendedButton();

private:
    void init_SubDetector_Widget();
    AwesomePropertyEditor *m_detectorTypeEditor;
    ColumnResizer *m_columnResizer;
    GroupBox *m_groupBox;
    DetectorItem *m_detectorItem;
    QWidget *m_subDetectorWidget;
};

#endif
