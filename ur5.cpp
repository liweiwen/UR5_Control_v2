#include "stdafx.h"
#include "tcp.h"
#include "ur5.h"
#include <stdio.h>
#include <math.h>
#include <vector>


#define PI 3.1415926535897932384626433832795028841971693993751058209

UR5_POSE ur5_pose;
CUR5::CUR5()
{
	m_tcp = new CTCP();
}

void CUR5::Connect(LPSTR lpAddress, INT nPort)
{
	m_tcp->Connect(lpAddress, nPort);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)RecvThread, this, NULL, NULL);
}

void CUR5::Move(double x, double y, double z, double rx, double ry, double rz)
{
	CHAR szCmd[0x100];
	sprintf(szCmd, "movel(p[%f, %f, %f, %f, %f, %f], a=1.2 ,v=0.05)\n",x,y,z,rx,ry,rz);
	m_tcp->Send(szCmd, strlen(szCmd));
}

void CUR5::Stop()
{
	m_tcp->Send("stopj(5.0)\n", strlen("stopj(5.0)\n"));
}

void CUR5::NormalizePose(PUR5_POSE pPose)
{
	if (pPose->rx < 0)
	{
		double theta = sqrt(pPose->rx * pPose->rx + pPose->ry * pPose->ry + pPose->rz * pPose->rz);
		double new_theta = 2 * PI - theta;
		pPose->rx = -pPose->rx / theta * new_theta;
		pPose->ry = -pPose->ry / theta * new_theta;
		pPose->rz = -pPose->rz / theta * new_theta;
	}
}

double ntohd(double d)
{
	double ret;
	unsigned char *p = (unsigned char *)&d;
	unsigned char *r = (unsigned char *)&ret;
	for (int i = 0; i < sizeof(double); i++)
	{
		r[i] = p[sizeof(double) - 1 - i];
	}
	return ret;
}

void CUR5::UpdateState(LPVOID lpBuffer, ULONG ulLength)
{
	memcpy(&ur5_pose, (PUCHAR)lpBuffer + 440, sizeof(UR5_POSE));
	ur5_pose.x = ntohd(ur5_pose.x);
	ur5_pose.y = ntohd(ur5_pose.y);
	ur5_pose.z = ntohd(ur5_pose.z);
	ur5_pose.rx = ntohd(ur5_pose.rx); 
	ur5_pose.ry = ntohd(ur5_pose.ry);
	ur5_pose.rz = ntohd(ur5_pose.rz);
	NormalizePose(&ur5_pose);
}

void CUR5::RecvThread(LPVOID IParam)
{
	CUR5 *pUr5 = (CUR5*)IParam ;
	while (true)
	{
		ULONG ulLength;
		pUr5->m_tcp->Recv(&ulLength, sizeof(ULONG));
		ulLength = ntohl(ulLength);
		LPVOID lpBuffer[0x1000];
		pUr5->m_tcp->Recv(lpBuffer, ulLength - sizeof(ULONG));
		pUr5->UpdateState(lpBuffer, ulLength - sizeof(ULONG));
	}
}

void CUR5::GetActualToolPose(PUR5_POSE pPose)
{	
	memcpy(pPose, &ur5_pose, sizeof(UR5_POSE));
}