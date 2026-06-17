#ifndef NGAN_HANG_CAU_HOI_H
#define NGAN_HANG_CAU_HOI_H

#include "du_lieu.h"

int sinhMaCauHoiMoi();
void hienThiMonHoc();
void hienThiCauHoiTheoMon();
void themCauHoi();
bool laCauHoiDungLoai(CauHoi ch, int maMonHoc, int loaiCauHoi);
int demCauHoiTheoMonVaLoai(int maMonHoc, int loaiCauHoi);
void menuNganHangCauHoi();

#endif
