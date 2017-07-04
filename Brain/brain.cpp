#include "brain.h"

#define BONE 3000
#define SKIN 800
#define BRAIN 1200
#define BACKGROUND 0
#define PI 3.1415926
#define min(x,y) (x>y?y:x)

//以下是vtk6.2.0以后使用API必须添加的宏
struct point{
	int x;
	int y;};


Brain::Brain(QWidget *parent)
	: QMainWindow(parent)
{
	this->setMinimumSize(800,500);
	this->setWindowIcon(QIcon(":Brain//Resources//build.png"));
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

Brain::~Brain(){}

void Brain::clickButton()
{
	QMessageBox::information(this, "My Tittle", "Hello World!");
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
	bt_showBrain=new QPushButton();  
    bt_showBrain->setText(tr("Show Brain")); 
	connect(bt_showBrain,SIGNAL(clicked()),this,SLOT(showBrainOnly()));
	
	bt_showBone=new QPushButton();  
    bt_showBone->setText(tr("Show Bone")); 
	connect(bt_showBone,SIGNAL(clicked()),this,SLOT(showBoneOnly()));

	bt_showSkin=new QPushButton();  
    bt_showSkin->setText(tr("Show Skin"));  
	connect(bt_showSkin,SIGNAL(clicked()),this,SLOT(showSkinOnly()));

	bt_showBrainPool=new QPushButton();  
    bt_showBrainPool->setText(tr("Show Brain Pool")); 
	connect(bt_showBrainPool,SIGNAL(clicked()),this,SLOT(showBrainPoolOnly()));

	bt_removeBack=new QPushButton();  
    bt_removeBack->setText(tr("Remove Background"));  
	connect(bt_removeBack,SIGNAL(clicked()),this,SLOT(removeBackground()));

	bt_info=new QPushButton();  
    bt_info->setText(tr("Information"));  
	connect(bt_info,SIGNAL(clicked()),this,SLOT(showInfo()));

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

	label1->setText(" Errors: 0");  
	label2->setText(" Warnings: 0");  
	label3->setText(" Messages: 0"); 

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

	edit->addAction(cut);
	edit->addAction(copy);
	edit->addAction(paste);	

	tool->addAction(printScreen);
	tool->addAction(seeLog);
	
	settings->addAction(defaults);
	settings->addAction(appearance);
	settings->addAction(view);
	settings->addAction(extension);
	settings->addAction(shortcutKey);

	help->addAction(about);
}

void Brain::setupToolBar()
{
	filetoolbar=new QToolBar("Open",NULL);
	filetoolbar->addAction(a_fileOpen);
	filetoolbar->addAction(a_save);
	filetoolbar->addAction(a_close);
	filetoolbar->addAction(copy);
	filetoolbar->addAction(cut);
	filetoolbar->addAction(paste);
	filetoolbar->addAction(printScreen);
	filetoolbar->addAction(seeLog);
	filetoolbar->addAction(view);
	
	//下拉框的标签
	QLabel *lab = new QLabel();
	lab->setText(" Views:"); 
	filetoolbar->addWidget(lab);

	//下拉框
	viewBox =new QComboBox();
	viewBox->addItem(QWidget::tr("Module"));  
    viewBox->addItem(QWidget::tr("Log message"));  
	viewBox->addItem(QWidget::tr("Download Samples")); 
	filetoolbar->addWidget(viewBox);

	this->addToolBar(filetoolbar);

	//搜索框
	searchLineEdit = new QLineEdit();	
	bt_search = new QPushButton();  
    bt_search->setFixedSize(20,20);  
    bt_search->setCursor(Qt::PointingHandCursor);  
    bt_search->setStyleSheet("QPushButton{border-image:url(:Brain/Resources/find.png);"  
                             "background:transparent;cursor:pointer;}");  
	
	
	QMargins margins = searchLineEdit->textMargins();//防止文本框输入内容位于按钮之下
	searchLineEdit->setTextMargins(margins.left(), margins.top(), bt_search->width(), margins.bottom());
	searchLineEdit->setPlaceholderText(QStringLiteral("Search"));
	
	QHBoxLayout *pSearchLayout = new QHBoxLayout();
	pSearchLayout->addStretch();
	pSearchLayout->addWidget(bt_search);
	pSearchLayout->setSpacing(0);
	pSearchLayout->setContentsMargins(0, 0, 0, 0);
	searchLineEdit->setLayout(pSearchLayout); 
	connect(bt_search, SIGNAL(clicked(bool)), this, SLOT(search()));
	filetoolbar->addWidget(searchLineEdit);

	
}
void Brain::search()
{
    QString strText = searchLineEdit->text();
    if (!strText.isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("Search"), QStringLiteral("Result:  %1").arg(strText));
    }
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
	connect(a_save, SIGNAL(triggered()), this, SLOT(fileSave(fileSave())));

	a_openExample=new QAction("Open Sample Example",this);	
	a_openExample->setIcon(QIcon(":Brain/Resources/MC.png"));
	connect(a_openExample, SIGNAL(triggered()), this, SLOT(fileOpen()));

	a_close=new QAction("Close file",this);
	a_close->setIcon(QIcon(":Brain/Resources/exit.png"));
	connect(a_close, SIGNAL(triggered()), this, SLOT(fileClose()));

	a_exit=new QAction("Exit",this);	
	a_exit->setIcon(QIcon(":Brain/Resources/find.png"));
	connect(a_exit, SIGNAL(triggered()), this, SLOT(fileClose()));
	//connect(, SIGNAL(triggered()), this, SLOT());
}

void Brain::createEditAction(){

	copy=new QAction("Copy",this);
	copy->setIcon(QIcon(":Brain/Resources/copy.png"));

	cut=new QAction("Cut",this);
	cut->setIcon(QIcon(":Brain/Resources/cut.png"));

	paste=new QAction("Paste",this);
	paste->setIcon(QIcon(":Brain/Resources/paste.png"));
}

void Brain::createToolAction(){

	printScreen = new QAction("Print Screen",this);
	printScreen->setIcon(QIcon(":Brain/Resources/box.png"));
	connect(printScreen, SIGNAL(triggered()), this, SLOT(createShortcutKeyDialog()));

	seeLog = new QAction("Log Message",this);
	seeLog->setIcon(QIcon(":Brain/Resources/about.png"));
	connect(seeLog, SIGNAL(triggered()), this, SLOT(createPrintScreenDialog()));
}

void Brain::createSettingsAction(){

	defaults = new QAction("Default",this);
	connect(defaults, SIGNAL(triggered()), this, SLOT((createDefaultsDialog())));

	appearance = new QAction("Appearance",this);
	connect(appearance, SIGNAL(triggered()), this, SLOT((clickButton())));

	view = new QAction("View",this);
	view->setIcon(QIcon(":Brain/Resources/edit.png"));

	extension = new QAction("Extension",this);
	shortcutKey = new QAction("ShortcutKey",this);	
}

void Brain::createHelpAction(){
	about = new QAction("About Brain.exe",this);
}


void Brain::createDefaultsDialog(){
    QDialog *dialog = new QDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(tr("Default Settings"));
	dialog->setMinimumSize(400,200);

	QWidget *part =new QWidget();

	QLabel *label1=new QLabel();
	label1->setText(" File Location: "); 

	QLineEdit *lineEdit = new QLineEdit();
	QToolButton *bt_fileLocation = new QToolButton();  
	bt_fileLocation->setText(tr("Browser")); 
	QCheckBox *checkbox1 = new QCheckBox("Show heap status",dialog);  
	QCheckBox *checkbox2 = new QCheckBox("Always run in background",dialog);  
	QCheckBox *checkbox3 = new QCheckBox("Build automatically",dialog);  
	QCheckBox *checkbox4 = new QCheckBox("Refresh on access",dialog);

	//布局管理
	QVBoxLayout *allLayout=new QVBoxLayout();
	QHBoxLayout *partLayout=new QHBoxLayout();

	partLayout->addWidget(lineEdit);
	partLayout->addWidget(bt_fileLocation);

	allLayout->addWidget(label1);
	allLayout->addWidget(part);
	allLayout->addWidget(checkbox1);
	allLayout->addWidget(checkbox2);
	allLayout->addWidget(checkbox3);
	allLayout->addWidget(checkbox4);

	dialog->setLayout(allLayout);
	part->setLayout(partLayout);
		
	dialog->show();
}

void Brain::createAppearanceDialog(){
	 QDialog *dialog = new QDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(tr("Appearance Settings"));
	dialog->setMinimumSize(400,200);

	QWidget *part1 =new QWidget();
	QWidget *part2 =new QWidget();

	QLabel *label1=new QLabel();
	label1->setText("Foreground color: "); 
	QLabel *label2=new QLabel();
	label2->setText("Background color: ");

	QRadioButton *radio0 = new QRadioButton("Black", this);
	radio0->setChecked(2);
	QRadioButton *radio1 = new QRadioButton("Red", this);  
	QRadioButton *radio2 = new QRadioButton("Yellow", this);  
	QRadioButton *radio3 = new QRadioButton("Green", this);  
	
	QRadioButton *radio4 = new QRadioButton("Write", this); 
	radio4->setChecked(1);
	QRadioButton *radio5 = new QRadioButton("Black", this);  	

	//布局管理
	QVBoxLayout *allLayout=new QVBoxLayout();
	QHBoxLayout *partLayout1=new QHBoxLayout();
	QHBoxLayout *partLayout2=new QHBoxLayout();

	partLayout1->addWidget(radio0);
	partLayout1->addWidget(radio1);
	partLayout1->addWidget(radio2);
	partLayout1->addWidget(radio3);

	part1->setLayout(partLayout1);

	partLayout2->addWidget(radio4);
	partLayout2->addWidget(radio5);

	part2->setLayout(partLayout2);

	allLayout->addWidget(label1);
	allLayout->addWidget(part1);
	allLayout->addWidget(label2);
	allLayout->addWidget(part2);

	dialog->setLayout(allLayout);
			
	dialog->show();

}

void Brain::createExtensionDialog(){
	QDialog *dialog = new QDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(tr("Extension Settings"));
	dialog->setMinimumSize(400,200);

	QWidget *part1 =new QWidget();
	QWidget *part2 =new QWidget();

	QLabel *label1=new QLabel();
	label1->setText(" Extension: "); 

	QLabel *label2=new QLabel();
	label2->setText(" Module_extension "); 

	QLabel *label3=new QLabel();
	label3->setText(" Print_screen_add_in"); 

	QToolButton *bt_extension1 = new QToolButton();
	QToolButton *bt_extension2 = new QToolButton();  
	bt_extension1->setText(tr("Edit")); 
	bt_extension2->setText(tr("Delete")); 

	QToolButton *bt_extension3 = new QToolButton();
	QToolButton *bt_extension4 = new QToolButton();  
	bt_extension3->setText(tr("Edit")); 
	bt_extension4->setText(tr("Delete")); 

	QToolButton *bt_extension5 = new QToolButton();  
	bt_extension5->setText(tr("Add")); 

	QVBoxLayout *allLayout=new QVBoxLayout();
	QHBoxLayout *partLayout1=new QHBoxLayout();
	QHBoxLayout *partLayout2=new QHBoxLayout();

	partLayout1->addWidget(label2);
	partLayout1->addWidget(bt_extension1);
	partLayout1->addWidget(bt_extension2);

	partLayout2->addWidget(label3);
	partLayout2->addWidget(bt_extension3);
	partLayout2->addWidget(bt_extension4);

	allLayout->addWidget(label1);
	allLayout->addWidget(part1);
	allLayout->addWidget(part2);
	allLayout->addWidget(bt_extension5);
	
	dialog->setLayout(allLayout);
	part1->setLayout(partLayout1);
	part2->setLayout(partLayout2);
	dialog->show();

}
void Brain::createShortcutKeyDialog(){
	QDialog *dialog = new QDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(tr("Shortcut Settings"));
	dialog->setMinimumSize(400,200);

	QWidget *part1 =new QWidget();
	QWidget *part2 =new QWidget();

	QLabel *label1=new QLabel();
	label1->setText(" Shortcut: "); 

	QLabel *label2=new QLabel();
	label2->setText("Save: Ctrl + S"); 

	QLabel *label3=new QLabel();
	label3->setText(" Print Screen: Ctrl + P"); 

	QToolButton *bt_extension1 = new QToolButton();
	QToolButton *bt_extension2 = new QToolButton();  
	bt_extension1->setText(tr("Edit")); 
	bt_extension2->setText(tr("Delete")); 

	QToolButton *bt_extension3 = new QToolButton();
	QToolButton *bt_extension4 = new QToolButton();  
	bt_extension3->setText(tr("Edit")); 
	bt_extension4->setText(tr("Delete")); 

	QToolButton *bt_extension5 = new QToolButton();  
	bt_extension5->setText(tr("Add")); 

	QVBoxLayout *allLayout=new QVBoxLayout();
	QHBoxLayout *partLayout1=new QHBoxLayout();
	QHBoxLayout *partLayout2=new QHBoxLayout();

	partLayout1->addWidget(label2);
	partLayout1->addWidget(bt_extension1);
	partLayout1->addWidget(bt_extension2);

	partLayout2->addWidget(label3);
	partLayout2->addWidget(bt_extension3);
	partLayout2->addWidget(bt_extension4);

	allLayout->addWidget(label1);
	allLayout->addWidget(part1);
	allLayout->addWidget(part2);
	allLayout->addWidget(bt_extension5);
	
	dialog->setLayout(allLayout);
	part1->setLayout(partLayout1);
	part2->setLayout(partLayout2);
	dialog->show();

}
void Brain::createPrintScreenDialog(){
	QString fileName = QFileDialog::getOpenFileName(this, tr("Save Screenshot"),".",tr("VTK files (*.png)"));
	if(fileName.isNull())
	return;
}

void Brain::fileOpen()
{
	//QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),".",tr("VTK files (*.png)"));
	//if(fileName.isNull())
		//return;

	//vtk读取dicom文件
	reader = vtkDICOMImageReader::New();
	reader->SetDataByteOrderToLittleEndian();
	reader->SetDirectoryName("C://Users//Kuangyan//Desktop//MRI-T1");
	reader->Update();
	reader->SetDataOrigin(0.0, 0.0, 0.0);//设置基准点

	data=reader->GetOutput();
	data->GetDimensions(dim);//获取图像维数
	double *spacing = reader->GetDataSpacing();


	//设置备份
	copyOfImg = new unsigned short[dim[0]*dim[1]*dim[2]];
	memcpy(copyOfImg,((unsigned short *)data->GetScalarPointer()),dim[0]*dim[1]*dim[2]*sizeof(unsigned short));
	unsigned short *image=(unsigned short *)(reader->GetOutput()->GetScalarPointer());

	readerImageCast = vtkImageCast::New();//数据类型转换
	readerImageCast->SetInputConnection(reader->GetOutputPort());
	readerImageCast->SetOutputScalarTypeToUnsignedShort ();
	readerImageCast->ClampOverflowOn();//阀值
		
	//设置不透明度传递函数,该函数确定各体绘像素或单位长度值的不透明度
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
	
	//设置颜色传递函数,该函数确定体绘像素的颜色值或者灰度值
	colorTransferFunction = vtkColorTransferFunction::New();
	colorTransferFunction->SetColorSpaceToRGB();

	colorTransferFunction->AddRGBPoint(1050, 1, 1, 1);
	colorTransferFunction->AddRGBPoint(1100, 0.5, 0.8, 0.5);
	colorTransferFunction->AddRGBPoint(1150, 0, 0, 0);
	colorTransferFunction->AddRGBPoint(1200, 0.5, 0.8, 0.5);
	colorTransferFunction->AddRGBPoint(1250, 1, 1, 1);
	
	volumeProperty = vtkVolumeProperty::New();
	//设定一个体绘容器的属性
		
	volumeProperty->SetScalarOpacity(opacityTransferFunction);//不透明度
	volumeProperty->ShadeOn();//影阴
	volumeProperty->SetInterpolationTypeToLinear();//直线与样条插值之间逐发函数
	volumeProperty->SetAmbient(0.2);//环境光系数
	volumeProperty->SetDiffuse(0.9);//漫反射
	volumeProperty->SetSpecular(0.2);//高光系数
	volumeProperty->SetSpecularPower(10); //高光强度 

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

	//定义Volume
	volume = vtkVolume::New();//表示透示图中的一组三维数据
	volume->SetMapper(gpuRayCastMapper);
	volume->SetProperty(volumeProperty);//设置体属性

	ren->AddVolume(volume);//将Volume装载到绘制类中
	//ren->SetBackground(255, 255, 255);
	ren->ResetCamera();

	widget->GetRenderWindow()->AddRenderer(ren);
	widget->update();
}

void Brain::fileSave()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),".",tr("VTK files (*.vtk)"), 0, QFileDialog::DontUseNativeDialog);
	if(fileName.isNull())
		return;	
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

//显示脑实质的函数
void Brain::showBrainOnly()
{
	restore();

	unsigned short *imgData=((unsigned short *)reader->GetOutput()->GetScalarPointer());

	//维度
	int height = dim[0];
	int width = dim[1];
	int level = dim[2];

	int average = 1100;//种子像素
	int threshold = 100;//阈值
	//如果所考虑的像素与种子像素灰度值差的绝对值小于阈值，则将该像素包括进种子像素所在区域	

	bool index=1;

	//种子标记
	bool *flag = new bool [width * height * level];//用来记录该像素是否属于种子区域
	memset(flag, 0, width * height * level * sizeof(bool));//memset是以字节为单位，初始化内存块。把每个数组单元初始化成任何想要的值。这里初始化为0。
	
	//将image041，初始化
	unsigned short *p = imgData + 10 * width * height;
	flag[10 * width * height + 128 * width + 128] = 1;
		
	int count=0;//记录种子像素个数

	while(index)
	{
		index=0;
		for (int i = 1;i < height;i++)
		{
			for (int j = 1;j < width - 1;j++)
			{
				if (flag[10 * width * height + i * width + j])
				{
					for(int u = -1;u < 2;u++)
					{
						for(int v = -1;v < 2;v++)
						{
							if(flag[10 * width * height + (i+u) * width + j + v] == 0 && abs(average - imgData[10 * width * height + (i + u) * width + j + v]) < threshold)
							{   //如果所考虑的像素与种子像素灰度值差的绝对值小于阈值，则将该像素包括进种子像素所在区域
								flag[10 * width * height + (i + u) * width + j + v] = 1;
								index = 1;
								count++;
							}
						}
					}
				}
			}
		}
	}
	
	index=1;

	while(index)
	{
		index=0;
		for (int k = 5; k < 44; k++)
		{
			for(int i = 1; i < height - 1; i++)
			{
				for(int j = 1; j < width - 1; j++)
				{
					if(flag[k * width * height + i * width + j])
					{
						for(int u = -1; u < 2; u++)
						{
							for(int v = -1; v < 2; v++)
							{
								for (int w = -1; w < 2; w++)
								{
									if(flag[(k+w)*width*height+(i+u)*width+j+v]==0 && abs(average-imgData[(k+w)*width*height+(i+u)*width+j+v])<threshold)
									{
										flag[(k+w)*width*height+(i+u)*width+j+v] = 1;
										index = 1;
									}
								}
							}
						}
					}
				}
			}
		}

	}

	for (int k = 0; k < level; k++)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				//如果该像素没有种子标记，将其像素值置为0
				////如果该像素有种子标记，则置为1200
				if (flag[k * height * width + i * width + j] == 0)
				{
					imgData[k * height * width + i * width + j] = 0;
				}
				else
				{
					imgData [k * height * width + i * width + j] = 1200;
				}
			}
		}
	}
	//显示分割后的图像
	showAll();
}

//移除颅骨的函数
void Brain::removeBone(unsigned short * image)
{
	int height = dim[0];
	int width = dim[1];
	int level = dim[2];
	unsigned short *dest = new unsigned short[height * width];

	//初始化dest
	for (int k = 0; k < level; k++)
	{
		memcpy(dest, image + k * width * height, 2 * width * height);//memset是以字节为单位，初始化内存块。把每个数组单元初始化成任何想要的值。
	
		int min = image[k * width * height];
		int max = image[k * width * height];

		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				if(image[k * width * height + i * width + j] > max)
				{
					max = image[k * width * height + i * width + j];
				}
				else if(image[k * width * height + i * width + j] < min)
				{
					min = image[k * width * height + i * width + j];
				}
			}
		}

		//计算出种子的大小
		int average = (min + max) / 2;
		int count = 0;

		while(count < 10)
		{
			int sumOfObj = 0;
			int sumOfBack = 0;
			int numOfObj = 0;
			int numOfBack = 0;

			for (int i = 0; i<height;i++)
			{
				for(int j=0;j<width;j++)
				{
					if (image[k * width * height + i * width + j] < average)
					{
						dest[i * width + j] = 0;
						sumOfBack += image[k * width * height + i * width + j];
						numOfBack++;
					} 
					else
					{
						dest[i * width + j] = BONE;
						sumOfObj += image[k * width * height + i * width + j];
						numOfObj++;
					}
				}
			}

			average=(sumOfObj / numOfObj + sumOfBack / numOfBack) / 2;
			count++;
		}		
		memcpy(image + k * width * height, dest, 2 * width * height);		
	}
	delete[] dest;
	this->statusBar()->showMessage(QString("%1").arg(QString::number(*((unsigned short *)reader->GetOutput()->GetScalarPointer()))), 5000);
}

//显示颅骨的函数
void Brain::showBoneOnly()
{
	restore();
	removeBone(((unsigned short *)reader->GetOutput()->GetScalarPointer()));
	showAll();
}

//显示皮肤的函数
void Brain::showSkinOnly()
{
	restore();
	unsigned short *dest=new unsigned short[dim[0]*dim[1]*dim[2]];
	memcpy(dest,copyOfImg,2*dim[0]*dim[1]*dim[2]);
	//image是去除背景之后的矩阵
	removeBone(dest);
	
	unsigned short *image=((unsigned short *)reader->GetOutput()->GetScalarPointer());
	int height=dim[0],width=dim[1],level=dim[2];

	int centerX=width/2,centerY=height/2;

	for (int k=0;k<level;k++)
	{
		for (double theta = 0; theta < 2 * PI; theta += 0.001)
		{
			int lim=min(centerY, centerX) - 1;
			int r=lim;
			while (r > 0)
			{
				int x=centerX+r*cos(theta);
				int y=centerY+r*sin(theta);

				if (x<width && y<height)
				{
					while (dest[k*width*height+y*width+x]!=BONE && r>=0)
					{
						image[k*width*height+y*width+x]=0;
						r--;
						x=centerX+r*cos(theta);
						y=centerY+r*sin(theta);
					}
					int dr=1;				
					int x0=centerX+(r+1)*cos(theta);
					int y0=centerY+(r+1)*sin(theta);
					image[k*width*height+y0*width+x0]=SKIN;

					x0=centerX+(r+2)*cos(theta);
					y0=centerY+(r+2)*sin(theta);
					image[k*width*height+y0*width+x0]=SKIN;					

					while(r>=0)
					{
						image[k*width*height+y*width+x]=0;
						r--;
						x=centerX+r*cos(theta);
						y=centerY+r*sin(theta);
					}
				}
				else
				{
					break;
				}
			}
			
		}
	}
	showAll();	
}

void Brain::showInfo()
{
	//显示信息的函数
	double headv=0;
	qDebug()<<dim[0]<<dim[1]<<dim[2];
	
	for(int i=0;i<dim[2];i++)
	{
		int count=0;
		count=dim[0]*dim[1]-RegionGrow_1((unsigned short *)reader->GetOutput()->GetScalarPointer()+i*dim[0]*dim[1],dim[0],dim[1]);
		qDebug()<<i<<"*********是***********"<<(unsigned short *)reader->GetOutput()->GetScalarPointer()+i*dim[0]*dim[1]<<"************"<<count;
		headv+=count;
	}

	double bHbili;
	qDebug()<<getBrainVol();
	qDebug()<<headv;
	bHbili=getBrainVol()/headv;
	biliShow=new bh();
	biliShow->bili->setText(QString::number(bHbili*100)+"%");
	biliShow->show();
}

void Brain::showAll()
{
	reader->Update();

	unsigned short *image=(unsigned short *)(reader->GetOutput()->GetScalarPointer());

	freeMemory();	
	readerImageCast = vtkImageCast::New();//数据类型转换
	readerImageCast->SetInputConnection(reader->GetOutputPort());
	readerImageCast->SetOutputScalarTypeToUnsignedShort ();
	readerImageCast->ClampOverflowOn();//阀值

	//设置不透明度传递函数//该函数确定各体绘像素或单位长度值的不透明度
	opacityTransferFunction = vtkPiecewiseFunction::New();//一维分段函数变换
	opacityTransferFunction->AddPoint(600, 0);
	opacityTransferFunction->AddPoint(800, 1);
	opacityTransferFunction->AddPoint(1150, 1);
	opacityTransferFunction->AddPoint(1200, 1);
	opacityTransferFunction->AddPoint(3600, 1);
	opacityTransferFunction->AddPoint(4000, 1);
	//opacityTransferFunction->AddPoint(736.25, 1.0);

	//设置颜色传递函数,该函数确定体绘像素的颜色值或者灰度值
	colorTransferFunction = vtkColorTransferFunction::New();
	colorTransferFunction->SetColorSpaceToRGB();
	colorTransferFunction->AddRGBPoint(20, 1, 1, 1);//添加色彩点（第一个参数索引）
	colorTransferFunction->AddRGBPoint(495, 1, 230.0/255, 170.0/255);
	colorTransferFunction->AddRGBPoint(1050, 1, 1, 1);
	colorTransferFunction->AddRGBPoint(1100, 0.5, 0.8, 0.5);
	colorTransferFunction->AddRGBPoint(1150, 0, 0, 0);
	colorTransferFunction->AddRGBPoint(1200, 0.5, 0.8, 0.5);
	colorTransferFunction->AddRGBPoint(1250, 1, 1, 1);

	volumeProperty = vtkVolumeProperty::New();//设定一个体绘容器的属性
	volumeProperty->SetScalarOpacity(opacityTransferFunction);//不透明度
	volumeProperty->SetColor(colorTransferFunction);//设置颜色
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

	//定义绘制者  GPU绘制
	//volumeMapper = vtkSmartVolumeMapper::New();   //体绘制器
	//volumeMapper->SetVolumeRayCastFunction(compositeFunction); //载入绘制方法
	//volumeMapper->SetRequestedRenderMode(vtkSmartVolumeMapper::GPURenderMode);
	//volumeMapper->SetInputConnection(readerImageCast->GetOutputPort());//图像数据输入
	//volumeMapper->SetNumberOfThreads(3);

	raycastMapper = vtkVolumeRayCastMapper::New();
	raycastMapper->SetVolumeRayCastFunction(compositeFunction);
	raycastMapper->SetInputConnection(readerImageCast->GetOutputPort());
	raycastMapper->SetNumberOfThreads(6);
	
	//定义Volume
	volume = vtkVolume::New();//表示透示图中的一组三维数据
	volume->SetMapper(raycastMapper);
	volume->SetProperty(volumeProperty);//设置体属性

	ren2->AddVolume(volume);//将Volume装载到绘制类中
	ren2->SetBackground(255, 255, 255);
	ren2->ResetCamera();

	//widget->cachedImageClean();
	
	//widget->cachedImage()->Delete();
	widget2->GetRenderWindow()->AddRenderer(ren2);
	widget2->update();
	this->statusBar()->showMessage(QString("%1").arg(QString::number(*((unsigned short *)reader->GetOutput()->GetScalarPointer()))), 5000);
}


void Brain::freeMemory(){
	
	ren2->RemoveVolume(volume);
	readerImageCast->Delete();
	opacityTransferFunction->Delete();
	colorTransferFunction->Delete();
	volumeProperty->Delete();
	compositeFunction->Delete();
	//volumeMapper->Delete();
	volume->Delete();	
	//ren->Delete();	
}

//恢复原图
void Brain::restore()
{
//memcpy用来做内存拷贝，可以拷贝任何数据类型的对象
	memcpy(((unsigned short *)reader->GetOutput()->GetScalarPointer()),copyOfImg,dim[0]*dim[1]*dim[2]*2);
}

void Brain::showBrainPoolOnly()
{
	restore();

	unsigned short *imgData=((unsigned short *)reader->GetOutput()->GetScalarPointer());
	int height=dim[0],width=dim[1],level=dim[2];

	int average=550;
	int threshold=130;
	bool index=1;

	bool *flag=new bool [width*height*level];
	memset(flag,0,width*height*level*sizeof(bool));

	//将image041，初始化
	//unsigned short *p = imgData+10*width*height;
	flag[19*width*height+128*width+128]=1;
	flag[19*width*height+128*width+144]=1;
	//cout<<imgData[19*width*height+128*width+128]<<endl;
	//int count=0;

	//初始化19层
	while(index)
	{
		index=0;
		for (int i=1;i<height;i++)
		{
			for (int j=1;j<width-1;j++)
			{
				if (flag[19*width*height+i*width+j])
				{
					for(int u=-1;u<2;u++)
					{
						for(int v=-1;v<2;v++)
						{
							if(flag[19*width*height+(i+u)*width+j+v]==0 && abs(average-imgData[19*width*height+(i+u)*width+j+v])<threshold)
							{
								flag[19*width*height+(i+u)*width+j+v]=1;
								//data[10*width*height+(i+u)*width+j+v]=1200;
								index=1;
								//count++;
							}
						}
					}
				}
			}
		}
	}

	index=1;

	while(index)
	{
		index=0;
		for (int k=17;k<=32;k++)
		{
			for(int i=1;i<height-1;i++)
			{
				for(int j=1;j<width-1;j++)
				{
					if(flag[k*width*height+i*width+j])
					{
						for(int u=-1;u<2;u++)
						{
							for(int v=-1;v<2;v++)
							{
								for (int w=-1;w<2;w++)
								{
									if(flag[(k+w)*width*height+(i+u)*width+j+v]==0 && abs(average-imgData[(k+w)*width*height+(i+u)*width+j+v])<threshold)
									{
										flag[(k+w)*width*height+(i+u)*width+j+v]=1;
										//data[(k+w)*width*height+(i+u)*width+j+v]=average;
										index=1;
									}
								}
							}
						}
					}
				}
			}
		}

	}

	for (int k=0;k<level;k++)
	{
		for (int i=0;i<height;i++)
		{
			for (int j=0;j<width;j++)
			{
				if (flag[k*height*width+i*width+j]==0)
				{
					imgData[k*height*width+i*width+j]=0;
				}
				else
				{
					imgData[k*height*width+i*width+j]=1200;
				}
			}
		}
	}

	showAll();
}

void Brain::removeBackground()
{

	unsigned short *imgData=((unsigned short *)reader->GetOutput()->GetScalarPointer());
	int height=dim[0],width=dim[1],level=dim[2];

	bool *flag=new bool [width*height];
	memset(flag,0,width*height);

	for(int i=0;i<width;i++)
	{
		flag[i]=1;
		flag[i+(height-1)*width]=1;
		*(imgData+i)=BACKGROUND;
		*(imgData+i+(height-1)*width)=BACKGROUND;
	}
	for(int i=0;i<height;i++)
	{
		flag[width*i]=1;
		flag[width-1+width*i]=1;
		*(imgData+width*i)=BACKGROUND;
		*(imgData+width-1+width*i)=BACKGROUND;
	}
	double average=0;	
	average+=*(imgData+1+1*width);
	flag[1+1*width]=1;
	*(imgData+1+1*width)=BACKGROUND;

	average+=*(imgData+1+(height-2)*width);
	flag[1+(height-2)*width]=1;
	*(imgData+1+(height-2)*width)=BACKGROUND;

	average+=*(imgData+width-2+1*width);
	flag[width-2+1*width]=1;
	*(imgData+width-2+1*width)=BACKGROUND;

	average+=*(imgData+width-2+(height-2)*width);
	flag[width-2+(height-2)*width]=1;
	*(imgData+width-2+(height-2)*width)=BACKGROUND;

	average/=4.0;
	//int count=2*(width+height);
	int threshold=200;

	bool index=1;

	for(int k=0;k<level;k++)
	{
		index=1;
		while(index)
		{
			index=0;
			for(int i=1;i<height-1;i++)
			{
				for(int j=1;j<width-1;j++)
				{
					if(flag[i*width+j])
					{
						for(int u=-1;u<2;u++)
						{
							for(int v=-1;v<2;v++)
							{
								if(flag[(i+u)*width+j+v]==0 && abs(average-*(imgData+(i+u)*width+j+v))<threshold)
								{
									flag[(i+u)*width+j+v]=1;
									*(imgData+(i+u)*width+j+v)=BACKGROUND;
									index=1;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Brain::showAllBrain()
{
	restore();
	removeBackground();
	showAll();
}

int  Brain::RegionGrow_1(unsigned short *data,int width,int height)
{
	bool *flag=new bool [width*height];
	memset(flag,0,width*height);

	for(int i=0;i<width;i++)
	{
		flag[i]=1;
		flag[i+(height-1)*width]=1;
		*(data+i)=0;
		*(data+i+(height-1)*width)=0;
	}
	for(int i=0;i<height;i++)
	{
		flag[width*i]=1;
		flag[width-1+width*i]=1;
		*(data+width*i)=0;
		*(data+width-1+width*i)=0;
	}

	double average=0;

	point seed={1,1};
	average+=*(data+seed.x+seed.y*width);
	flag[seed.x+seed.y*width]=1;
	*(data+seed.x+seed.y*width)=0;
	
	seed.x=1;
	seed.y=height-2;
	average+=*(data+seed.x+seed.y*width);
	flag[seed.x+seed.y*width]=1;
	*(data+seed.x+seed.y*width)=0;
	
	seed.x=width-2;
	seed.y=1;
	average+=*(data+seed.x+seed.y*width);
	flag[seed.x+seed.y*width]=1;
	*(data+seed.x+seed.y*width)=0;
	
	seed.x=width-2;
	seed.y=height-2;
	average+=*(data+seed.x+seed.y*width);
	flag[seed.x+seed.y*width]=1;
	*(data+seed.x+seed.y*width)=0;
	
	average/=4.0;
	int count=2*(width+height);
	int threshold=100;
	
	bool index=1;
	while(index)
	{
		index=0;
		for(int i=1;i<height-1;i++)
		{
			for(int j=1;j<width-1;j++)
			{
				if(flag[i*width+j])
				{
					for(int u=-1;u<2;u++)
					{
						for(int v=-1;v<2;v++)
						{
							if(flag[(i+u)*width+j+v]==0 && abs(average-*(data+(i+u)*width+j+v))<threshold)
							{
								flag[(i+u)*width+j+v]=1;
								*(data+(i+u)*width+j+v)=0;
								count++;
								index=1;
							}
						}
					}
				}
			}
		}
	}

	int tmpNum = 0;

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(*(data+i*width+j)>=2500)
			{
				*(data+i*	+j)=0;
				++tmpNum;
			}

		}
	}
	qDebug()<<"???????????????"<<count;

	cout<<tmpNum<<endl;
	return count + tmpNum;
}

int Brain::getBrainVol()
{
	restore();
	//显示大脑的函数

	unsigned short *imgData=((unsigned short *)reader->GetOutput()->GetScalarPointer());
	int height=dim[0],width=dim[1],level=dim[2];

	int average=1100;
	int threshold=200;
	bool index=1;

	bool *flag=new bool [width*height*level];
	memset(flag,0,width*height*level*sizeof(bool));

	//将image041，初始化
	unsigned short *p = imgData+10*width*height;
	flag[10*width*height+128*width+128]=1;
	cout<<imgData[10*width*height+128*width+128]<<endl;
	double count=0;

	while(index)
	{
		index=0;
		for (int i=1;i<height;i++)
		{
			for (int j=1;j<width-1;j++)
			{
				if (flag[10*width*height+i*width+j])
				{
					for(int u=-1;u<2;u++)
					{
						for(int v=-1;v<2;v++)
						{
							if(flag[10*width*height+(i+u)*width+j+v]==0 && abs(average-imgData[10*width*height+(i+u)*width+j+v])<threshold)
							{
								flag[10*width*height+(i+u)*width+j+v]=1;
								//data[10*width*height+(i+u)*width+j+v]=1200;
								index=1;
								count++;
							}
						}
					}
				}
			}
		}
	}
	
	index=1;

	while(index)
	{
		index=0;

		for (int k=5;k<44;k++)
		{
			for(int i=1;i<height-1;i++)
			{
				for(int j=1;j<width-1;j++)
				{
					if(flag[k*width*height+i*width+j])
					{
						for(int u=-1;u<2;u++)
						{
							for(int v=-1;v<2;v++)
							{
								for (int w=-1;w<2;w++)
								{
									if(flag[(k+w)*width*height+(i+u)*width+j+v]==0 && abs(average-imgData[(k+w)*width*height+(i+u)*width+j+v])<threshold)
									{
										flag[(k+w)*width*height+(i+u)*width+j+v]=1;
										//data[(k+w)*width*height+(i+u)*width+j+v]=average;
										index=1;
										count++;
									}
								}
							}
						}
					}
				}
			}
		}

	}
	return count;
}