#ifndef BRAIN_H
#define BRAIN_H
//6.0以后需添加以下宏
#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)  
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include "ui_brain.h"
#include "bh.h"

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QAction>
#include <QtGui/QIcon>
#include <QtCore/QDebug>
#include <QtWidgets/QSplitter>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QDialog>
#include <QtWidgets/QRadioButton> 

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "vtkVolumeProperty.h"
#include "vtkVolumeRayCastIsosurfaceFunction.h"
#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkVolumeRayCastMapper.h"
#include "vtkGPUVolumeRayCastMapper.h"
#include "vtkOpenGLGPUVolumeRayCastMapper.h"
#include "vtkVolumeMapper.h"
#include "vtkVolume.h"
#include "vtkDICOMImageReader.h"
#include "vtkImageCast.h"
#include "vtkStructuredPointsWriter.h"
#include "vtkStructuredPointsReader.h"
#include "vtkImageCast.h"
#include "vtkMarchingCubes.h" 
#include "vtkImageShrink3D.h"
#include "vtkDecimatePro.h"
#include "vtkSmoothPolyDataFilter.h"
#include "vtkPolyDataNormals.h"
#include "vtkStripper.h"
#include "vtkPolyDataMapper.h"
#include "vtkLODActor.h" 
#include "vtkPolyDataWriter.h"
#include "vtkImageSeedConnectivity.h"
#include "vtkImageShiftScale.h"
#include "vtkImageMathematics.h"
#include "vtkImageThreshold.h"
#include "vtkImageData.h"
#include "vtkCommand.h"
#include "vtkImplicitPlaneWidget.h"
#include "vtkPlane.h"
#include "vtkBoxWidget.h"
#include "vtkPlanes.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCamera.h"
#include "vtkStructuredPointsWriter.h"
#include "vtkSmartVolumeMapper.h"
#include <vtkSmartPointer.h>
#include <QVTKWidget.h>

class Brain : public QMainWindow
{
	Q_OBJECT//加了这个才能用信号和槽

public:
	Brain(QWidget *parent = 0);
	~Brain();

signals:
	void canShowSkin();

private slots:
	void fileOpen();
	void fileSave();
	void fileClose();
	void mousePressEvent(QMouseEvent *eve);
	void showBrainOnly();
	void showBoneOnly();
	void showSkinOnly();
	void showBrainPoolOnly();
	void showAllBrain();
	void removeBackground();
	void removeBone(unsigned short * image);
	int  RegionGrow_1(unsigned short *data,int width,int height);
	void showInfo();
	int getBrainVol();
	void restore();
	void showAll();
	void freeMemory();
	void search();
	void clickButton();
	void createDefaultsDialog();
	void createAppearanceDialog();
	void createExtensionDialog();
	void createShortcutKeyDialog();
	void createPrintScreenDialog();

private:
	QVTKWidget *widget;
	QVTKWidget *widget2;

	QWidget *moduleDockWidget;
	QWidget *logDockWidget;
	vtkImageData *data;
	vtkDICOMImageReader *reader,*reader1;
	vtkImageCast *readerImageCast;
	vtkPiecewiseFunction *opacityTransferFunction;
	vtkColorTransferFunction *colorTransferFunction;
	vtkVolumeProperty *volumeProperty;
	vtkVolumeRayCastCompositeFunction *compositeFunction;
	vtkSmartVolumeMapper *volumeMapper;
	vtkVolumeRayCastMapper *raycastMapper;
	vtkGPUVolumeRayCastMapper *gpuRayCastMapper;
	vtkOpenGLGPUVolumeRayCastMapper *glRayCastMapper;
	vtkVolumeMapper *mapper;
	vtkVolume *volume;
	int dim[3];
	vtkRenderer *ren;
	vtkRenderer *ren2;

	//menu
	QMenu *file;
	QMenu *edit;
	QMenu *tool;
	QMenu *settings;
	QMenu *help;

	//工具栏
	QToolBar *filetoolbar;

	QLineEdit *searchLineEdit;
	//搜索框
	QPushButton *bt_search;
	//下拉框
	QComboBox * viewBox;

	//file
	QAction *a_fileOpen;
	QAction *a_save;
	QAction *a_close;
	QAction *a_exit;
	QAction *a_openExample;

	//edit
	QAction *cut;
	QAction *copy;
	QAction *paste;

	//tool
	QAction *printScreen;
	QAction *seeLog;

	//setting
	QAction *defaults;
	QAction *appearance;
	QAction *view;
	QAction *extension;
	QAction *shortcutKey;

	//help	
	QAction *about;	

	QDockWidget *dc_module;
	QDockWidget *dc_log;

	QVBoxLayout *boxLayout;
	QGridLayout *GridLayout;

	//the buttons of the modules
	QPushButton  *bt_showBrain;
	QPushButton  *bt_showBone;
	QPushButton  *bt_showSkin;
	QPushButton  *bt_showBrainPool;
	QPushButton  *bt_removeBack;
	QPushButton  *bt_info;

	unsigned short * copyOfImg;
	void setupMenu();
	void setupToolBar();
	void setupDock();
	void createAction();
	void createFileAction();
	void createEditAction();
	void createSettingsAction();
	void createToolAction();
	void createHelpAction();	
	bh *biliShow; 

};
#endif // BRAIN_H
