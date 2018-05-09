#pragma once
#include <Windows.h>
#include "tcp.h"

typedef struct _UR5_POSE {
	double x;
	double y;
	double z;
	double rx;
	double ry;
	double rz;
}UR5_POSE, *PUR5_POSE, *LPUR5_POSE;




class CUR5
{
public:
	CUR5();
public:
	void Connect(LPSTR lpAddress, INT nPort);
	void NormalizePose(PUR5_POSE pPose);
	void GetActualToolPose(PUR5_POSE pPose);

	void Move(double x, double y, double z, double rx, double ry, double rz);

	void Stop();

private:
	static void RecvThread(LPVOID lParam);
	void UpdateState(LPVOID lpBuffer, ULONG ulLength);
private:
	CTCP *m_tcp;


};