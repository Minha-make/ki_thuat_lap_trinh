#include "thi_bao_cao.h"

void themCauHoiVaoDeThi(int chiSoCauHoi, vector<CauHoiThi>& deThi) {
    CauHoiThi chThi;
    chThi.maCauHoi = dsCauHoi[chiSoCauHoi].maCauHoi;
    chThi.dapAnDaChon = -1;
    chThi.thuTuDapAn.clear();

    for (int j = 0; j < SO_DAP_AN; j++) {
        chThi.thuTuDapAn.push_back(j);
    }

    xaoTronVectorSoNguyen(chThi.thuTuDapAn);
    deThi.push_back(chThi);
}

// Chon ngau nhien mot so cau hoi theo loai de/kho de dua vao de.
void themCauHoiTheoLoaiVaoDe(int maMonHoc, int loaiCauHoi, int soCauCanLay, vector<CauHoiThi>& deThi) {
    vector<int> chiSo;

    for (int i = 0; i < static_cast<int>(dsCauHoi.size()); i++) {
        if (laCauHoiDungLoai(dsCauHoi[i], maMonHoc, loaiCauHoi)) {
            chiSo.push_back(i);
        }
    }

    xaoTronVectorSoNguyen(chiSo);

    for (int i = 0; i < soCauCanLay; i++) {
        themCauHoiVaoDeThi(chiSo[i], deThi);
    }
}

// Sinh de thi theo so cau de, so cau kho va xao tron toan bo de.
void sinhDeThi(int maMonHoc, int soCauDe, int soCauKho, vector<CauHoiThi>& deThi) {
    themCauHoiTheoLoaiVaoDe(maMonHoc, 1, soCauDe, deThi);
    themCauHoiTheoLoaiVaoDe(maMonHoc, 2, soCauKho, deThi);

    vector<int> thuTuCauHoi;
    for (int i = 0; i < static_cast<int>(deThi.size()); i++) {
        thuTuCauHoi.push_back(i);
    }

    xaoTronVectorSoNguyen(thuTuCauHoi);

    vector<CauHoiThi> deThiDaXaoTron;
    for (int i = 0; i < static_cast<int>(deThi.size()); i++) {
        deThiDaXaoTron.push_back(deThi[thuTuCauHoi[i]]);
    }

    deThi = deThiDaXaoTron;
}

// Kiem tra thoi gian lam bai da vuot qua gioi han hay chua.
bool hetGio(time_t batDau, int soPhut) {
    return difftime(time(NULL), batDau) >= soPhut * 60;
}

// Cho thi sinh tra loi tung cau, kiem tra dap an hop le va gio lam bai.
void lamBaiThi(vector<CauHoiThi>& deThi, int soPhut, int& thoiGianLamBaiGiay) {
    time_t batDau = time(NULL);

    for (int i = 0; i < static_cast<int>(deThi.size()); i++) {
        if (hetGio(batDau, soPhut)) {
            cout << "\nDa het gio. He thong tu dong thu bai.\n";
            break;
        }

        int viTri = timCauHoi(deThi[i].maCauHoi);
        CauHoi ch = dsCauHoi[viTri];

        cout << "\nCau " << i + 1 << ": " << ch.noiDung << "\n";
        for (int j = 0; j < SO_DAP_AN; j++) {
            int chiSoDapAn = deThi[i].thuTuDapAn[j];
            cout << char('A' + j) << ". " << ch.dapAn[chiSoDapAn] << "\n";
        }

        while (true) {
            string traLoi;
            cout << "Nhap dap an A/B/C/D, bo trong neu khong tra loi: ";
            getline(cin, traLoi);
            traLoi = catKhoangTrang(traLoi);

            if (traLoi == "") {
                deThi[i].dapAnDaChon = -1;
                break;
            }

            if ((int)traLoi.length() != 1) {
                cout << "Dap an khong hop le. Chi duoc nhap A, B, C, D hoac bo trong.\n";
                continue;
            }

            char c = traLoi[0];
            if (c >= 'a' && c <= 'd') c = char(c - 'a' + 'A');

            if (c < 'A' || c > 'D') {
                cout << "Dap an khong hop le. Chi duoc nhap A, B, C, D hoac bo trong.\n";
                continue;
            }

            int dapAnHienThi = c - 'A';
            deThi[i].dapAnDaChon = deThi[i].thuTuDapAn[dapAnHienThi];
            break;
        }
    }

    thoiGianLamBaiGiay = (int)difftime(time(NULL), batDau);
}

// ==================================================
// 9. CHAM DIEM VA BAO CAO
// ==================================================

// Dem so cau tra loi dung trong de thi.
int demCauDung(vector<CauHoiThi>& deThi) {
    int dem = 0;
    for (int i = 0; i < static_cast<int>(deThi.size()); i++) {
        int viTri = timCauHoi(deThi[i].maCauHoi);
        if (viTri != -1 && deThi[i].dapAnDaChon == dsCauHoi[viTri].dapAnDung) {
            dem++;
        }
    }
    return dem;
}

// Sinh ma ket qua moi bang cach lay ma lon nhat cong mot.
int sinhMaKetQuaMoi() {
    int maLonNhat = 0;
    for (int i = 0; i < static_cast<int>(dsKetQua.size()); i++) {
        if (dsKetQua[i].maKetQua > maLonNhat) {
            maLonNhat = dsKetQua[i].maKetQua;
        }
    }
    return maLonNhat + 1;
}

// Luu ket qua thi vao danh sach va ghi file, diem duoc tinh lai khi can.
void luuKetQua(int maThiSinh, int maMonHoc, int tongSoCau, int soCauDung, int thoiGianLamBaiGiay) {
    KetQuaThi kq;
    kq.maKetQua = sinhMaKetQuaMoi();
    kq.maThiSinh = maThiSinh;
    kq.maMonHoc = maMonHoc;
    kq.tongSoCau = tongSoCau;
    kq.soCauDung = soCauDung;
    kq.thoiGianThi = layThoiGianHienTai();
    kq.thoiGianLamBaiGiay = thoiGianLamBaiGiay;

    dsKetQua.push_back(kq);
    ghiDuLieu();

    cout << "\n===== KET QUA THI =====\n";
    cout << "So cau dung: " << soCauDung << "/" << tongSoCau << "\n";
    cout << fixed << setprecision(2);
    cout << "Diem: " << tinhDiem(soCauDung, tongSoCau) << "\n";
    cout << "Thoi gian lam bai: " << thoiGianLamBaiGiay << " giay\n";
}

// Cau hinh de thi, sinh de, cho lam bai va cham diem.
void batDauThi() {
    if (static_cast<int>(dsThiSinh.size()) == 0 || static_cast<int>(dsMonHoc.size()) == 0 || static_cast<int>(dsCauHoi.size()) == 0) {
        cout << "Chua co du du lieu de thi.\n";
        return;
    }

    cout << "\nDANH SACH THI SINH\n";
    for (int i = 0; i < static_cast<int>(dsThiSinh.size()); i++) {
        cout << dsThiSinh[i].maThiSinh << ". " << dsThiSinh[i].hoTen << "\n";
    }

    int maThiSinh = nhapSo("Nhap ma thi sinh: ", 1, 1000000);
    if (timThiSinh(maThiSinh) == -1) {
        cout << "Thi sinh khong ton tai.\n";
        return;
    }

    hienThiMonHoc();
    int maMonHoc = nhapSo("Nhap ma mon hoc: ", 1, 1000000);
    if (timMonHoc(maMonHoc) == -1) {
        cout << "Mon hoc khong ton tai.\n";
        return;
    }

    int soCauDeCoSan = demCauHoiTheoMonVaLoai(maMonHoc, 1);
    int soCauKhoCoSan = demCauHoiTheoMonVaLoai(maMonHoc, 2);
    cout << "So cau hoi de co san: " << soCauDeCoSan << "\n";
    cout << "So cau hoi kho co san: " << soCauKhoCoSan << "\n";

    int soCauDe = nhapSo("Nhap so cau hoi de trong de thi: ", 0, soCauDeCoSan);
    int soCauKho = nhapSo("Nhap so cau hoi kho trong de thi: ", 0, soCauKhoCoSan);
    while (soCauDe + soCauKho == 0) {
        cout << "De thi phai co it nhat 1 cau hoi.\n";
        soCauDe = nhapSo("Nhap lai so cau hoi de: ", 0, soCauDeCoSan);
        soCauKho = nhapSo("Nhap lai so cau hoi kho: ", 0, soCauKhoCoSan);
    }

    int tongSoCau = soCauDe + soCauKho;
    int soPhut = nhapSo("Nhap thoi gian lam bai phut: ", 1, 300);

    vector<CauHoiThi> deThi;
    sinhDeThi(maMonHoc, soCauDe, soCauKho, deThi);

    int thoiGianLamBaiGiay = 0;
    lamBaiThi(deThi, soPhut, thoiGianLamBaiGiay);

    int soCauDung = demCauDung(deThi);
    luuKetQua(maThiSinh, maMonHoc, tongSoCau, soCauDung, thoiGianLamBaiGiay);
}

// Hien thi tat ca ket qua thi va thong ke diem co ban.
void hienThiBaoCaoKetQua() {
    if (static_cast<int>(dsKetQua.size()) == 0) {
        cout << "Chua co ket qua thi.\n";
        return;
    }

    cout << "\nBAO CAO KET QUA NHIEU LAN THI\n";
    cout << left
         << setw(8) << "MaKQ"
         << setw(8) << "MaTS"
         << setw(8) << "MaMH"
         << setw(10) << "Tong"
         << setw(10) << "Dung"
         << setw(10) << "Diem"
         << setw(22) << "Thoi gian"
         << setw(8) << "Giay" << "\n";

    double diemDauTien = tinhDiem(dsKetQua[0].soCauDung, dsKetQua[0].tongSoCau);
    double tongDiem = 0;
    double caoNhat = diemDauTien;
    double thapNhat = diemDauTien;

    for (int i = 0; i < static_cast<int>(dsKetQua.size()); i++) {
        KetQuaThi kq = dsKetQua[i];
        double diem = tinhDiem(kq.soCauDung, kq.tongSoCau);
        cout << left
             << setw(8) << kq.maKetQua
             << setw(8) << kq.maThiSinh
             << setw(8) << kq.maMonHoc
             << setw(10) << kq.tongSoCau
             << setw(10) << kq.soCauDung
             << setw(10) << fixed << setprecision(2) << diem
             << setw(22) << kq.thoiGianThi
             << setw(8) << kq.thoiGianLamBaiGiay << "\n";

        tongDiem += diem;
        if (diem > caoNhat) caoNhat = diem;
        if (diem < thapNhat) thapNhat = diem;
    }

    cout << "\nSo lan thi: " << static_cast<int>(dsKetQua.size()) << "\n";
    cout << "Diem cao nhat: " << caoNhat << "\n";
    cout << "Diem thap nhat: " << thapNhat << "\n";
    cout << "Diem trung binh: " << tongDiem / static_cast<int>(dsKetQua.size()) << "\n";
}

// ==================================================
// 10. MENU CHUONG TRINH
// ==================================================

// Hien thi menu chinh va dieu huong cac chuc nang lon.
void menuChinh() {
    while (true) {
        cout << "\n===== CHUONG TRINH THI TRAC NGHIEM =====\n";
        cout << "1. Quan ly ngan hang cau hoi\n";
        cout << "2. Cau hinh de thi va bat dau thi\n";
        cout << "3. Bao cao ket qua thi\n";
        cout << "0. Luu va thoat\n";

        int chon = nhapSo("Chon: ", 0, 3);
        if (chon == 0) {
            ghiDuLieu();
            cout << "Da luu du lieu.\n";
            return;
        }
        if (chon == 1) menuNganHangCauHoi();
        if (chon == 2) {
            batDauThi();
            tamDung();
        }
        if (chon == 3) {
            hienThiBaoCaoKetQua();
            tamDung();
        }
    }
}

// ==================================================
// 11. HAM MAIN
// ==================================================


