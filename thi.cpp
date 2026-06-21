#include "thi.h"

#include "bao_cao.h"
#include <conio.h>
#include <windows.h>

// Nhap dap an theo kieu khong chan chuong trinh, giup van kiem tra duoc het gio khi nguoi dung khong bam phim.
// Tra ve true neu da nhap xong mot dap an; tra ve false neu het gio trong luc dang doi nhap.
bool nhapDapAn(time_t batDau, int soPhut, int& dapAnDaChonTheoViTriHienThi) {
    cout << "Nhap dap an A/B/C/D, bo trong neu khong tra loi: ";

    while (!hetGio(batDau, soPhut)) {
        if (!_kbhit()) {
            Sleep(50);
            continue;
        }

        int phim = _getch();

        if (phim == '\r' || phim == '\n') {
            cout << "\n";
            dapAnDaChonTheoViTriHienThi = -1;
            return true;
        }

        char c = static_cast<char>(phim);
        if (c >= 'a' && c <= 'd') c = char(c - 'a' + 'A');

        if (c >= 'A' && c <= 'D') {
            cout << c << "\n";
            dapAnDaChonTheoViTriHienThi = c - 'A';
            return true;
        }

        cout << "\nDap an khong hop le. Chi duoc nhap A, B, C, D hoac Enter de bo qua.\n";
        cout << "Nhap dap an A/B/C/D, bo trong neu khong tra loi: ";
    }

    return false;
}

// Tao mot cau hoi trong de thi tu cau hoi goc va xao tron thu tu dap an hien thi.
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

// Chon ngau nhien mot so cau hoi theo loai de/kho de dua vao de thi.
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

// Sinh de thi theo so cau de/kho, sau do xao tron lai thu tu cac cau trong de.
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

// Kiem tra thoi gian lam bai da vuot qua gioi han soPhut hay chua.
bool hetGio(time_t batDau, int soPhut) {
    return difftime(time(NULL), batDau) >= soPhut * 60;
}

// Cho thi sinh tra loi tung cau, chi nhan A/B/C/D hoac bo trong, va tu dong thu bai khi het gio.
void lamBaiThi(vector<CauHoiThi>& deThi, int soPhut, int& thoiGianLamBaiGiay) {
    time_t batDau = time(NULL);

    for (int i = 0; i < static_cast<int>(deThi.size()); i++) {
        if (hetGio(batDau, soPhut)) {
            cout << "\nDa het gio. He thong tu dong thu bai.\n";
            break;
        }

        int viTri = timCauHoi(deThi[i].maCauHoi);
        if (viTri == -1) {
            cout << "\nKhong tim thay cau hoi trong ngan hang. Bo qua cau nay.\n";
            continue;
        }
        CauHoi ch = dsCauHoi[viTri];

        cout << "\nCau " << i + 1 << ": " << ch.noiDung << "\n";
        for (int j = 0; j < SO_DAP_AN; j++) {
            int chiSoDapAn = deThi[i].thuTuDapAn[j];
            cout << char('A' + j) << ". " << ch.dapAn[chiSoDapAn] << "\n";
        }

        int dapAnHienThi = -1;
        bool daNhapXong = nhapDapAn(batDau, soPhut, dapAnHienThi);

        if (!daNhapXong) {
            cout << "\nDa het gio. He thong tu dong thu bai.\n";
            break;
        }

        if (dapAnHienThi == -1) {
            deThi[i].dapAnDaChon = -1;
        } else {
            deThi[i].dapAnDaChon = deThi[i].thuTuDapAn[dapAnHienThi];
        }
    }

    thoiGianLamBaiGiay = (int)difftime(time(NULL), batDau);
}

// Dieu phoi mot lan thi: chon thi sinh, chon mon, nhap cau hinh, sinh de, lam bai, cham diem.
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
