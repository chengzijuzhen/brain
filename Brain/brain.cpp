#include "brain.h"
#include "core.h"

Brain::Brain(QWidget *parent)
	: QMainWindow(parent)
{
	this->setMinimumSize(800,500);
	createAction();
	setupMenu();
	setupToolBar();
	setupDock();

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

void Brain::setupDock()
{
	//module dock
    dc_module=new QDockWidget(tr("Modules"),this);  
    dc_module->setFeatures(QDockWidget::AllDockWidgetFeatures); 
    addDockWidget(Qt::LeftDockWidgetArea,dc_module);  

	moduleDockWidget = new QWidget();
	dc_module->setWidget(moduleDockWidget); 

	// All of the buttons in module dock
	bt_showBrain=new QPushButton;  
    bt_showBrain->setText(tr("Show Brain")); 

	bt_showBone=new QPushButton;  
    bt_showBone->setText(tr("Show Bone")); 

	bt_showSkin=new QPushButton;  
    bt_showSkin->setText(tr("Show Skin"));  

	bt_showBrainPool=new QPushButton;  
    bt_showBrainPool->setText(tr("Show Brain Pool"));  

	bt_removeBack=new QPushButton;  
    bt_removeBack->setText(tr("Remove Background"));  

	bt_info=new QPushButton;  
    bt_info->setText(tr("Information"));  

	boxLayout =new QVBoxLayout();
	boxLayout->addWidget(bt_showBrain);
	boxLayout->addWidget(bt_showBone);
	boxLayout->addWidget(bt_showSkin);
	boxLayout->addWidget(bt_showBrainPool);
	boxLayout->addWidget(bt_removeBack);
	boxLayout->addWidget(bt_info);
	boxLayout->setSpacing(10);
	moduleDockWidget->setLayout(boxLayout);
	moduleDockWidget->show();

//the background of dock widget
/*
	moduleDockWidget->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background, QColor(192,253,123));
	//palette.setBrush(QPalette::Background, QBrush(QPixmap(":/images/1.jpg")));
	moduleDockWidget->setPalette(palette); 
*/
	
	//log dock
	dc_log=new QDockWidget(tr("Log messages"),this);  
    dc_log->setFeatures(QDockWidget::AllDockWidgetFeatures);  

    logDockWidget = new QWidget();
	dc_log->setWidget(logDockWidget); 

	QLabel *label1 = new QLabel();  
   	QLabel *label2 = new QLabel();  
	QLabel *label3 = new QLabel();  
	QLabel *label4 = new QLabel();  
	QLabel *label5 = new QLabel();  
	QLabel *label6 = new QLabel();  

	label1->setText(" Errors: 2");  
	label2->setText(" Warnings: 5");  
	label3->setText(" Messages: 4"); 

	label4->setPixmap(QPixmap(":Brain//Resources//clear.png"));
	label5->setPixmap(QPixmap(":Brain//Resources//gotocell.png"));
	label6->setPixmap(QPixmap(":Brain//Resources//new.png"));

	GridLayout =new QGridLayout();
	GridLayout->addWidget(label1,0,2);
	GridLayout->addWidget(label2,1,2);
	GridLayout->addWidget(label3,2,2);
	GridLayout->addWidget(label4,0,1);
	GridLayout->addWidget(label5,1,1);
	GridLayout->addWidget(label6,2,1);
	logDockWidget->setLayout(GridLayout);

	addDockWidget(Qt::LeftDockWidgetArea,dc_log); 
	logDockWidget->show();
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
	file->addAction(a_openExample);
	file->addAction(a_close);
	file->addAction(a_exit);

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
	settings->addAction(extensions);
	settings->addAction(shortcutKey);

	help->addAction(about);
}

void Brain::setupToolBar()
{
	filetoolbar=new QToolBar("Open",NULL);
	filetoolbar->addAction(a_fileOpen);
	filetoolbar->addAction(a_save);
	filetoolbar->addAction(a_close);
	filetoolbar->addAction(a_exit);
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
	connect(a_save, SIGNAL(triggered()), this, SLOT(fileSave(fileOpen())));

	a_openExample=new QAction("Open Sample Example",this);	
	connect(a_openExample, SIGNAL(triggered()), this, SLOT());

	a_close=new QAction("Close file",this);
	a_close->setIcon(QIcon(":Brain/Resources/exit.png"));
	connect(a_close, SIGNAL(triggered()), this, SLOT(fileClose()));

	a_exit=new QAction("Exit",this);	
	a_exit->setIcon(QIcon(":Brain/Resources/find.png"));
	connect(a_exit, SIGNAL(triggered()), this, SLOT(fileClose()));
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
	connect(showBrainPool,SIGNAL(triggered()),this,SLOT(removeBackground()));

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
	extensions = new QAction("Extensions",this);
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
	reader->SetDataOrigin(0.0, 0.0, 0.0);//设置基准点

	data=reader->GetOutput();
	data->GetDimensions(dim);
	qDebug()<<dim[0]<<" "<<dim[1]<<" "<<dim[2]<<"\n";
	double *spacing = reader->GetDataSpacing();
	qDebug()<<*spacing<<" "<<*(spacing+1)<<" "<<*(spacing+2)<<"\n";

	//设置备份
	copyOfImg = new unsigned short[dim[0]*dim[1]*dim[2]];
	memcpy(copyOfImg,((unsigned short *)data->GetScalarPointer()),dim[0]*dim[1]*dim[2]*sizeof(unsigned short));
			
	unsigned short *image=(unsigned short *)(reader->GetOutput()->GetScalarPointer());

		
	readerImageCast = vtkImageCast::New();//数据类型转换
	readerImageCast->SetInputConnection(reader->GetOutputPort());
	readerImageCast->SetOutputScalarTypeToUnsignedShort ();
	readerImageCast->ClampOverflowOn();//阀值

	
	//设置不透明度传递函数//该函数确定各体绘像素或单位长度值的不透明度
	opacityTransferFunction = vtkPiecewiseFunction::New();//一维分段函数变换
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
		

	//设置颜色传递函数,该函数确定体绘像素的颜色值或者灰度值
	colorTransferFunction = vtkColorTransferFunction::New();
	colorTransferFunction->SetColorSpaceToRGB();
	//colorTransferFunction->AddRGBPoint(20, 1, 1, 1);//添加色彩点（第一个参数索引）
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
	//设定一个体绘容器的属性
		
	volumeProperty->SetScalarOpacity(opacityTransferFunction);//不透明度
	//volumeProperty->SetColor(colorTransferFunction);//设置颜色
	volumeProperty->ShadeOn();//影阴
	volumeProperty->SetInterpolationTypeToLinear();//直线与样条插值之间逐发函数
	volumeProperty->SetAmbient(0.2);//环境光系数
	volumeProperty->SetDiffuse(0.9);//漫反射
	volumeProperty->SetSpecular(0.2);//高光系数
	volumeProperty->SetSpecularPower(10); //高光强度 

	//定义光线投射方法为MIP体绘制方法,MIP为体绘制经典算法
	//  vtkVolumeRayCastMIPFunction*mipRaycastFunction = vtkVolumeRayCastMIPFunction::New();
	//  mipRaycastFunction->SetMaximizeMethodToOpacity();

	compositeFunction = vtkVolumeRayCastCompositeFunction::New();
	//运行沿着光线合成

	//定义绘制者
	raycastMapper = vtkVolumeRayCastMapper::New();
	raycastMapper->SetVolumeRayCastFunction(compositeFunction);
	raycastMapper->SetInputConnection(readerImageCast->GetOutputPort());
	raycastMapper->SetNumberOfThreads(8);

	gpuRayCastMapper = vtkGPUVolumeRayCastMapper::New();
	gpuRayCastMapper->SetInputConnection(readerImageCast->GetOutputPort());
	gpuRayCastMapper->SetBlendModeToComposite();
	gpuRayCastMapper->SetAutoAdjustSampleDistances(1);

	//volumeMapper = vtkSmartVolumeMapper::New();   //体绘制器
	//volumeMapper->SetVolumeRayCastFunction(compositeFunction); //载入绘制方法
	//volumeMapper->SetRequestedRenderMode(vtkSmartVolumeMapper::GPURenderMode);
	//volumeMapper->SetInputConnection(readerImageCast->GetOutputPort());//图像数据输入
	
	//glRayCastMapper = vtkOpenGLGPUVolumeRayCastMapper::New();
	//glRayCastMapper->SetInputConnection(readerImageCast->GetOutputPort());
	
	
	//volumeMapper->SetNumberOfThreads(3);

	//定义Volume
	volume = vtkVolume::New();//表示透示图中的一组三维数据
	volume->SetMapper(gpuRayCastMapper);
	volume->SetProperty(volumeProperty);//设置体属性

	//ren = vtkRenderer::New();
	ren->AddVolume(volume);//将Volume装载到绘制类中
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

