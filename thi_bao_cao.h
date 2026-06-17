#ifndef THI_BAO_CAO_H
#define THI_BAO_CAO_H

#include "ngan_hang_cau_hoi.h"

void themCauHoiVaoDeThi(int chiSoCauHoi, vector<CauHoiThi>& deThi);
void themCauHoiTheoLoaiVaoDe(int maMonHoc, int loaiCauHoi, int soCauCanLay, vector<CauHoiThi>& deThi);
void sinhDeThi(int maMonHoc, int soCauDe, int soCauKho, vector<CauHoiThi>& deThi);
bool hetGio(time_t batDau, int soPhut);
void lamBaiThi(vector<CauHoiThi>& deThi, int soPhut, int& thoiGianLamBaiGiay);
int demCauDung(vector<CauHoiThi>& deThi);
int sinhMaKetQuaMoi();
void luuKetQua(int maThiSinh, int maMonHoc, int tongSoCau, int soCauDung, int thoiGianLamBaiGiay);
void batDauThi();
void hienThiBaoCaoKetQua();
void menuChinh();

#endif
