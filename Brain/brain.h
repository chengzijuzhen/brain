#ifndef BRAIN_H
#define BRAIN_H
//6.0以后需添加以下宏
#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)  
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include <QtWidgets/QMainWindow>
#include "ui_brain.h"

#include <QtWidgets/QLabel>

//#pragma comment( lib, "qlabel.lib")

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
#include "bh.h"

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
		//QLabel *label;

private:
	QLabel *label;
	QLabel *label1;
	QVTKWidget *widget;
	QVTKWidget *widget2;
	
	//QVTKWidget *widget1;
	vtkRenderer *ren;
	vtkRenderer *ren2;
	vtkDICOMImageReader *reader,*reader1;
	vtkImageData *data;
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
	//Ui::QtTestClass ui;
	QMenu *file;
	QMenu *edit;
	QMenu *menuAbout;

	QToolBar *filetoolbar;


	QAction *a_fileOpen;
	QAction *a_save;
	QAction *a_close;

	QAction *showBrain;
	QAction *showBone;
	QAction *showSkin;
	QAction *showBrainPool;
	QAction *removeBack;

	QAction *info;


	int dim[3];
	unsigned short * copyOfImg;
	void setupMenu();
	void setupToolBar();
	void createAction();
	void showAll();
	void freeMemory();

	void restore();
	bh *biliShow; 
};

#endif // BRAIN_H
