#include "core.h"
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

void Core::showBrainOnly()
{
	restore();
	//显示大脑的函数

	unsigned short *imgData=((unsigned short *)reader->GetOutput()->GetScalarPointer());
	int height=dim[0],width=dim[1],level=dim[2];

	int average=1100;
	int threshold=100;
	bool index=1;

	bool *flag=new bool [width*height*level];
	memset(flag,0,width*height*level*sizeof(bool));

	//将image041，初始化
	unsigned short *p = imgData+10*width*height;
	flag[10*width*height+128*width+128]=1;
	cout<<imgData[10*width*height+128*width+128]<<endl;
	int count=0;

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

void Core::removeBone(unsigned short * image)
{
	//restore();
	//Qt::WindowFlags
	//显示骨头的函数
	int height=dim[0],width=dim[1],level=dim[2];
	unsigned short *dest=new unsigned short[height*width];

	for (int k=0;k<level;k++)
	{
		//unsigned short *image=((unsigned short *)reader->GetOutput()->GetScalarPointer())+k*height*width;

		//unsigned short *dest=new unsigned short[height*width];

		memcpy(dest,image+k*width*height,2*width*height);

		int min=image[k*width*height],max=image[k*width*height];
		for(int i=0;i<height;i++)
		{
			for (int j=0;j<width;j++)
			{
				if (image[k*width*height+i*width+j]>max)
				{
					max=image[k*width*height+i*width+j];
				}
				else if (image[k*width*height+i*width+j]<min)
				{
					min=image[k*width*height+i*width+j];
				}
			}
		}

		int average=(min+max)/2;
		int count=0;


		while(count<10)
		{
			int sumOfObj=0;
			int sumOfBack=0;
			int numOfObj=0;
			int numOfBack=0;
			for (int i=0;i<height;i++)
			{
				for(int j=0;j<width;j++)
				{
					if (image[k*width*height+i*width+j]<average)
					{
						dest[i*width+j]=0;
						sumOfBack+=image[k*width*height+i*width+j];
						numOfBack++;
					} 
					else
					{
						dest[i*width+j]=BONE;
						sumOfObj+=image[k*width*height+i*width+j];
						numOfObj++;
					}
				}
			}

			average=(sumOfObj/numOfObj+sumOfBack/numOfBack)/2;
			count++;
		}
		
		memcpy(image+k*width*height,dest,2*width*height);

		
	}
	delete [] dest;
	this->statusBar()->showMessage(QString("%1").arg(QString::number(*((unsigned short *)reader->GetOutput()->GetScalarPointer()))), 5000);
	
	
	//showAll();
	showSkin->setEnabled(true);
}


void Core::showBoneOnly()
{
	restore();
	removeBone(((unsigned short *)reader->GetOutput()->GetScalarPointer()));
	showAll();
}


void Core::showSkinOnly()
{
	restore();
	//removeBackground();

	unsigned short *dest=new unsigned short[dim[0]*dim[1]*dim[2]];
	memcpy(dest,copyOfImg,2*dim[0]*dim[1]*dim[2]);

	removeBone(dest);
	
	
	//显示皮肤的函数
	//image是去除背景之后的矩阵
	
	unsigned short *image=((unsigned short *)reader->GetOutput()->GetScalarPointer());
	int height=dim[0],width=dim[1],level=dim[2];

	int centerX=width/2,centerY=height/2;

	for (int k=0;k<level;k++)
	{
		for (double theta=0;theta<2*PI;theta+=0.001)
		{
			
			int lim=min(centerY,centerX)-1;
			int r=lim;
			while (r>0)
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
					/*
					int x0=centerX+(r+dr)*cos(theta);
					int y0=centerY+(r+dr)*sin(theta);
					while (image[k*width*height+y0*width+x0]!=BACKGROUND)
					{
						image[k*width*height+y0*width+x0]=SKIN;
						++dr;
						x0=centerX+(r+dr)*cos(theta);
						y0=centerY+(r+dr)*sin(theta);
					}
					*/
					
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

	delete [] dest;
	//memcpy(((unsigned short *)reader->GetOutput()->GetScalarPointer()),dest,2*dim[0]*dim[1]*dim[2]);
	showAll();
	
	
}

void Core::showInfo()
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

void Core::showAll()
{
	reader->Update();


	unsigned short *image=(unsigned short *)(reader->GetOutput()->GetScalarPointer());

	for (int k=21;k<=51;k++)
	{
		//memset(image+k*dim[0]*dim[1],0,2*dim[0]*dim[1]);
	}

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
	//colorTransferFunction->AddRGBPoint(2000, 0, 0, 1);
	//colorTransferFunction->AddRGBPoint(2048, 0, 1, 0);
	//
	//colorTransferFunction->AddRGBPoint(4000, 0.8, 0.8, 0.8);

	volumeProperty = vtkVolumeProperty::New();
	//设定一个体绘容器的属性

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


void Core::freeMemory()
{
	
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

void Core::restore()
{
	memcpy(((unsigned short *)reader->GetOutput()->GetScalarPointer()),copyOfImg,dim[0]*dim[1]*dim[2]*2);
}

void Core::showBrainPoolOnly()
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

void Core::removeBackground()
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
	//TRACE()
	//memcpy(data,flag,2*width*height);
}

void Core::showAllBrain()
{
	restore();
	removeBackground();
	showAll();
}

int  Core::RegionGrow_1(unsigned short *data,int width,int height)
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
	//TRACE()
	//memcpy(data,flag,2*width*height);
	return count+tmpNum;
}

int Core::getBrainVol()
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