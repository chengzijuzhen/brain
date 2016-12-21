#ifndef BRAIN_H
#define BRAIN_H
//6.0以后需添加以下宏
#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)  
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include "ui_brain.h"
#include "core.h"
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
	Q_OBJECT

public:
	Brain(QWidget *parent = 0);
	~Brain();

signals:
	void canShowSkin();

public slots:
		void fileOpen();
		void fileSave();
		void fileClose();
		void mousePressEvent(QMouseEvent *eve);

private:
	QVTKWidget *widget;
	QVTKWidget *widget2;
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
		//Ui::QtTestClass ui;
	QMenu *file;
	QMenu *edit;
	QMenu *tool;
	QMenu *settings;
	QMenu *help;

	QToolBar *filetoolbar;

	//file
	QAction *a_fileOpen;
	QAction *a_save;
	QAction *a_close;
	QAction *a_exit;
	QAction *a_openExample;

	//edit
	QAction *showBrain;
	QAction *showBone;
	QAction *showSkin;
	QAction *showBrainPool;
	QAction *removeBack;
	QAction *info;

	//tool
	QAction *printScreen;
	QAction *seeLog;

	//setting
	QAction *defaults;
	QAction *appearance;
	QAction *views;
	QAction *extensions;
	QAction *shortcutKey;

	//help	
	QAction *about;	

	unsigned short * copyOfImg;
	void setupMenu();
	void setupToolBar();

	void createAction();
	void createFileAction();
	void createEditAction();
	void createSettingsAction();
	void createToolAction();
	void createHelpAction();	
};
#endif // BRAIN_H
