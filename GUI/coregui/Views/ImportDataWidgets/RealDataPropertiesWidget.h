// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/RealDataPropertiesWidget.h
//! @brief     Defines class RealDataPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALDATAPROPERTIESWIDGET_H
#define REALDATAPROPERTIESWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class LinkInstrumentManager;
class SessionItem;
class InstrumentModel;
class RealDataModel;
class RealDataItem;
class QDataWidgetMapper;
class QLineEdit;
class QComboBox;

//! The RealDataPropertiesWidget class holds instrument selector to link with RealDataItem.
//! Part of RealDataSelectorWidget, resides at lower left corner of ImportDataView.

class BA_CORE_API_ RealDataPropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RealDataPropertiesWidget(QWidget *parent = 0);

    QSize sizeHint() const { return QSize(64, 135); }
    QSize minimumSizeHint() const { return QSize(64, 128); }

    void setModels(InstrumentModel *instrumentModel, RealDataModel *realDataModel);
    void setItem(SessionItem *item);

public slots:
    void onInstrumentComboIndexChanged(int index);
    void onInstrumentMapUpdate();
    void onRealDataPropertyChanged(const QString &name);

private:
    void setComboToIdentifier(const QString &identifier);
    void setComboConnected(bool isConnected);

    LinkInstrumentManager *m_linkManager;
    QDataWidgetMapper *m_dataNameMapper;
    QLineEdit *m_dataNameEdit;
    QComboBox *m_instrumentCombo;
    QString m_current_id;
    RealDataItem *m_currentDataItem;
};

#endif
