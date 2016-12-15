#include "brain.h"
#include "core.h"

Brain::Brain(QWidget *parent)
	: QMainWindow(parent)
{
	
	//Qt::WindowFlags
	//ui.setupUi(this);
	this->setMinimumSize(800,600);
	//QSplitter *splitterMain=new QSplitter(Qt::Horizontal,this);
	//splitterMain->setHandleWidth(5);
	//splitterMain->setStyleSheet("QSplitter::handle { background-color: RGB(255,0,0) }");
	//label=new QLabel("splitter test",0);
	//label1=new QLabel("hello",0);
	//splitterMain->addWidget(label);
	createAction();
	setupMenu();
	setupToolBar();
	
	widget=new QVTKWidget;
	widget->update();
	/*widget->setAutoFillBackground(1);*/
	widget2=new QVTKWidget;
	widget2->update();
	/*widget2->setAutoFillBackground(1);*/

	//splitterMain->addWidget(widget);
	//splitterMain->addWidget(label1);
	//this->setCentralWidget(splitterMain);
	QSplitter * mainSplitter = new QSplitter(Qt::Horizontal);
	mainSplitter->addWidget(widget);
	mainSplitter->addWidget(widget2);
	/*mainSplitter->setAutoFillBackground(true);*/
	ren = vtkRenderer::New();
	ren2= vtkRenderer::New();

	this->setCentralWidget(mainSplitter);
}

Brain::~Brain()
{

}

void Brain::setupMenu()
{
	//file=new QMenu("File",this);
	
	file=menuBar()->addMenu("File");
	edit=menuBar()->addMenu("Edit");
	tool=menuBar()->addMenu("Tool");
	settings=menuBar()->addMenu("Settings");
	help=menuBar()->addMenu("Help");

	file->addAction(a_fileOpen);
	file->addAction(a_save);
	file->addAction(downloadExample);
	file->addAction(a_close);
	file->addAction(exit);
	//file->setIcon(QIcon());

	edit->addAction(showBrain);
	edit->addAction(showBone);
	edit->addAction(showSkin);
	edit->addAction(showBrainPool);
	edit->addAction(removeBack);
	edit->addAction(info);

	tool->addAction(printScreen);
	tool->addAction(seeLog);
	
	settings->addAction(defaults);
	settings->addAction(appearance);
	settings->addAction(views);
	settings->addAction(display);
	settings->addAction(extension);
	settings->addAction(shortcutKey);
	settings->addAction(layout);
	
	help->addAction(about);
}

void Brain::setupToolBar()
{
	filetoolbar=new QToolBar("Open",NULL);
	filetoolbar->addAction(a_fileOpen);
	filetoolbar->addAction(a_save);
	filetoolbar->addAction(a_close);

	this->addToolBar(filetoolbar);
}

void Brain::createAction()
{
	createFileAction();
	createEditAction();
	createToolAction();
	createSettingsAction();
	createHelpAction();
}

void Brain::createFileAction()
{
	a_fileOpen=new QAction("Open file",this);
	a_fileOpen->setIcon(QIcon(":/Brain/Resources/open.png"));
	connect(a_fileOpen, SIGNAL(triggered()), this, SLOT(fileOpen()));

	a_save=new QAction("Save file",this);
	a_save->setIcon(QIcon(":Brain/Resources/save.png"));
	connect(a_save, SIGNAL(triggered()), this, SLOT(fileSave()));

	downloadExample=new QAction("Download Sample Example",this);	
	//connect(, SIGNAL(triggered()), this, SLOT());

	a_close=new QAction("Close",this);
	a_close->setIcon(QIcon(":Brain/Resources/exit.png"));
	connect(a_close, SIGNAL(triggered()), this, SLOT(fileClose()));

	exit=new QAction("Exit",this);	
	//connect(, SIGNAL(triggered()), this, SLOT());
}

void Brain::createEditAction(){

	showBrain=new QAction("Show Brain",this);
	connect(showBrain,SIGNAL(triggered()),this,SLOT(showBrainOnly()));

	showBone=new QAction("Show Bone",this);
	connect(showBone,SIGNAL(triggered()),this,SLOT(showBoneOnly()));

	showSkin=new QAction("Show Skin",this);
	//showSkin->setEnabled(false);
	connect(showSkin,SIGNAL(triggered()),this,SLOT(showSkinOnly()));

	showBrainPool=new QAction("Show Ventricle",this);
	connect(showBrainPool,SIGNAL(triggered()),this,SLOT(showBrainPoolOnly()));

	removeBack=new QAction("Remove Background",this);
	connect(removeBack,SIGNAL(triggered()),this,SLOT(showAllBrain()));

	info=new QAction("Information",this);
	connect(info,SIGNAL(triggered()),this,SLOT(showInfo()));
}


void Brain::createToolAction(){

	printScreen = new QAction("Print Screen",this);
	seeLog = new QAction("See Log Messages",this);	

}

void Brain::createSettingsAction(){

	defaults = new QAction("Defaults",this);
	appearance = new QAction("Appearance",this);
	views = new QAction("Views",this);
	display = new QAction("Display",this);
	extension = new QAction("Extension",this);
	layout = new QAction("Layout",this);
	shortcutKey = new QAction("ShortcutKey",this);	
}

void Brain::createHelpAction(){

	about = new QAction("About Brain.exe",this);
}


void Brain::fileOpen()
{
	//QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),".",tr("VTK files (*.png)"));
	//if(fileName.isNull())
		//return;

	reader = vtkDICOMImageReader::New();
	reader->SetDataByteOrderToLittleEndian();
	reader->SetDirectoryName("C://Users//Kuangyan//Desktop//MRI-T1");
	reader->Update();
	reader->SetDataOrigin(0.0, 0.0, 0.0);//���û�׼��

	data=reader->GetOutput();
	data->GetDimensions(dim);
	qDebug()<<dim[0]<<" "<<dim[1]<<" "<<dim[2]<<"\n";
	double *spacing = reader->GetDataSpacing();
	qDebug()<<*spacing<<" "<<*(spacing+1)<<" "<<*(spacing+2)<<"\n";

	//���ñ���
	copyOfImg = new unsigned short[dim[0]*dim[1]*dim[2]];
	memcpy(copyOfImg,((unsigned short *)data->GetScalarPointer()),dim[0]*dim[1]*dim[2]*sizeof(unsigned short));
			
	unsigned short *image=(unsigned short *)(reader->GetOutput()->GetScalarPointer());

		
	readerImageCast = vtkImageCast::New();//��������ת��
	readerImageCast->SetInputConnection(reader->GetOutputPort());
	readerImageCast->SetOutputScalarTypeToUnsignedShort ();
	readerImageCast->ClampOverflowOn();//��ֵ

	
	//���ò�͸���ȴ��ݺ���//�ú���ȷ����������ػ�λ����ֵ�Ĳ�͸����
	opacityTransferFunction = vtkPiecewiseFunction::New();//һά�ֶκ����任
	opacityTransferFunction->AddPoint(400, 0);
	opacityTransferFunction->AddPoint(800, 0);
	opacityTransferFunction->AddPoint(1050, 0);
	opacityTransferFunction->AddPoint(1150, 1);
	opacityTransferFunction->AddPoint(1200, 1);
	opacityTransferFunction->AddPoint(1300, 1);
	opacityTransferFunction->AddPoint(1350, 1);
	opacityTransferFunction->AddPoint(1400, 0);
	opacityTransferFunction->AddPoint(3600, 0);
	opacityTransferFunction->AddPoint(4000, 0);
	//opacityTransferFunction->AddPoint(736.25, 1.0);
		

	//������ɫ���ݺ���,�ú���ȷ��������ص���ɫֵ���߻Ҷ�ֵ
	colorTransferFunction = vtkColorTransferFunction::New();
	colorTransferFunction->SetColorSpaceToRGB();
	//colorTransferFunction->AddRGBPoint(20, 1, 1, 1);//���ɫ�ʵ㣨��һ������������
	//colorTransferFunction->AddRGBPoint(495, 1, 230.0/255, 170.0/255);
	colorTransferFunction->AddRGBPoint(1050, 1, 1, 1);
	colorTransferFunction->AddRGBPoint(1100, 0.5, 0.8, 0.5);
	colorTransferFunction->AddRGBPoint(1150, 0, 0, 0);
	colorTransferFunction->AddRGBPoint(1200, 0.5, 0.8, 0.5);
	colorTransferFunction->AddRGBPoint(1250, 1, 1, 1);
	//colorTransferFunction->AddRGBPoint(2000, 0, 0, 1);
	//colorTransferFunction->AddRGBPoint(2048, 0, 1, 0);
	//
	//colorTransferFunction->AddRGBPoint(4000, 0.8, 0.8, 0.8);

	volumeProperty = vtkVolumeProperty::New();
	//�趨һ���������������
		
	volumeProperty->SetScalarOpacity(opacityTransferFunction);//��͸����
	//volumeProperty->SetColor(colorTransferFunction);//������ɫ
	volumeProperty->ShadeOn();//Ӱ��
	volumeProperty->SetInterpolationTypeToLinear();//ֱ����������ֵ֮���𷢺���
	volumeProperty->SetAmbient(0.2);//������ϵ��
	volumeProperty->SetDiffuse(0.9);//������
	volumeProperty->SetSpecular(0.2);//�߹�ϵ��
	volumeProperty->SetSpecularPower(10); //�߹�ǿ�� 

	//�������Ͷ�䷽��ΪMIP����Ʒ���,MIPΪ����ƾ����㷨
	//  vtkVolumeRayCastMIPFunction*mipRaycastFunction = vtkVolumeRayCastMIPFunction::New();
	//  mipRaycastFunction->SetMaximizeMethodToOpacity();

	compositeFunction = vtkVolumeRayCastCompositeFunction::New();
	//�������Ź��ߺϳ�

	//���������
	raycastMapper = vtkVolumeRayCastMapper::New();
	raycastMapper->SetVolumeRayCastFunction(compositeFunction);
	raycastMapper->SetInputConnection(readerImageCast->GetOutputPort());
	raycastMapper->SetNumberOfThreads(8);

	gpuRayCastMapper = vtkGPUVolumeRayCastMapper::New();
	gpuRayCastMapper->SetInputConnection(readerImageCast->GetOutputPort());
	gpuRayCastMapper->SetBlendModeToComposite();
	gpuRayCastMapper->SetAutoAdjustSampleDistances(1);

	//volumeMapper = vtkSmartVolumeMapper::New();   //�������
	//volumeMapper->SetVolumeRayCastFunction(compositeFunction); //������Ʒ���
	//volumeMapper->SetRequestedRenderMode(vtkSmartVolumeMapper::GPURenderMode);
	//volumeMapper->SetInputConnection(readerImageCast->GetOutputPort());//ͼ����������
	
	//glRayCastMapper = vtkOpenGLGPUVolumeRayCastMapper::New();
	//glRayCastMapper->SetInputConnection(readerImageCast->GetOutputPort());
	
	
	//volumeMapper->SetNumberOfThreads(3);

	//����Volume
	volume = vtkVolume::New();//��ʾ͸ʾͼ�е�һ����ά����
	volume->SetMapper(gpuRayCastMapper);
	volume->SetProperty(volumeProperty);//����������

	//ren = vtkRenderer::New();
	ren->AddVolume(volume);//��Volumeװ�ص���������
	ren->SetBackground(255, 255, 255);
	ren->ResetCamera();

	//widget->cachedImageClean();
	widget->GetRenderWindow()->AddRenderer(ren);
	
	widget->update();

	//QApplication::overrideCursor();
}

void Brain::fileSave()
{
	/*
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),".",tr("VTK files (*.vtk)"), 0, QFileDialog::DontUseNativeDialog);
	
	if(fileName.isNull())
		return;
	*/
}

void Brain::fileClose()
{
	Brain::Brain();
}

void Brain::mousePressEvent(QMouseEvent *eve)
{
	//label1->setText(QString("%1,%2").arg(QString::number(eve->x()),QString::number(eve->y())));
	statusBar()->showMessage(QString("%1,%2").arg(QString::number(eve->x()),QString::number(eve->y())),5000);
}

