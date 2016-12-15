#ifndef CORE_H
#define CORE_H
//6.0�Ժ���������º�
#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)  
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include <QtWidgets/QMainWindow>
#include "ui_brain.h"
#include "bh.h"
#include "brain.h"

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

class Core : public QMainWindow
{
	Q_OBJECT

public:
	Core(QWidget *parent = 0);
	~Core();

signals:
	void canShowSkin();

public slots:
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

private:private:
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
	QAction *exit;
	QAction *downloadExample;

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
	QAction *display;
	QAction *extension;
	QAction *shortcutKey;
	QAction *layout;

	//help	
	QAction *about;	

	QLabel *label;
	QLabel *label1;
		
	bh *biliShow; 
	unsigned short * copyOfImg;
};
#endif // CORE_H
