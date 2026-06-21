#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "bao_cao.h"
#include "ngan_hang_cau_hoi.h"
#include "thi.h"
#include "tien_ich.h"

using namespace std;

int soTestDat = 0;
int soTestLoi = 0;

void kiemTra(bool dieuKien, string tenTest) {
    if (dieuKien) {
        cout << "[PASS] " << tenTest << "\n";
        soTestDat++;
    } else {
        cout << "[FAIL] " << tenTest << "\n";
        soTestLoi++;
    }
}

bool ganBangDouble(double a, double b) {
    return fabs(a - b) < 0.000001;
}

void choNguoiDungXemKetQua() {
    cout << "\nNhan Enter de thoat...";
    string tam;
    getline(cin, tam);
}

CauHoi taoCauHoi(int maCauHoi, int maMonHoc, int mucDo, int dapAnDung) {
    CauHoi ch;
    ch.maCauHoi = maCauHoi;
    ch.maMonHoc = maMonHoc;
    ch.mucDo = mucDo;
    ch.noiDung = "Noi dung cau hoi";
    ch.dapAn[0] = "A";
    ch.dapAn[1] = "B";
    ch.dapAn[2] = "C";
    ch.dapAn[3] = "D";
    ch.dapAnDung = dapAnDung;
    return ch;
}

bool laHoanViDapAnHopLe(vector<int> thuTuDapAn) {
    sort(thuTuDapAn.begin(), thuTuDapAn.end());
    if (static_cast<int>(thuTuDapAn.size()) != SO_DAP_AN) return false;
    for (int i = 0; i < SO_DAP_AN; i++) {
        if (thuTuDapAn[i] != i) return false;
    }
    return true;
}

void khoiTaoDuLieuMau() {
    dsMonHoc.clear();
    dsCauHoi.clear();
    dsThiSinh.clear();
    dsKetQua.clear();

    dsMonHoc.push_back({1, "Ky thuat lap trinh"});
    dsMonHoc.push_back({2, "Cau truc du lieu"});

    dsThiSinh.push_back({1, "Nguyen Van A"});
    dsThiSinh.push_back({2, "Tran Thi B"});

    dsCauHoi.push_back(taoCauHoi(1, 1, 1, 0));
    dsCauHoi.push_back(taoCauHoi(2, 1, 1, 1));
    dsCauHoi.push_back(taoCauHoi(3, 1, 2, 2));
    dsCauHoi.push_back(taoCauHoi(4, 1, 2, 3));
    dsCauHoi.push_back(taoCauHoi(5, 2, 1, 0));

    KetQuaThi kq1;
    kq1.maKetQua = 3;
    kq1.maThiSinh = 1;
    kq1.maMonHoc = 1;
    kq1.tongSoCau = 5;
    kq1.soCauDung = 4;
    kq1.thoiGianThi = "2026-06-21 10:00:00";
    kq1.thoiGianLamBaiGiay = 120;
    dsKetQua.push_back(kq1);

    KetQuaThi kq2 = kq1;
    kq2.maKetQua = 8;
    dsKetQua.push_back(kq2);
}

void testTienIch() {
    kiemTra(catKhoangTrang("  abc \t") == "abc", "catKhoangTrang cat dau/cuoi chuoi");
    kiemTra(catKhoangTrang("\r\n abc def \n") == "abc def", "catKhoangTrang xu ly xuong dong");

    kiemTra(laSoNguyen("123"), "laSoNguyen nhan chuoi so hop le");
    kiemTra(laSoNguyen(" 001 "), "laSoNguyen chap nhan khoang trang dau/cuoi");
    kiemTra(!laSoNguyen("12a"), "laSoNguyen tu choi ky tu chu");
    kiemTra(!laSoNguyen(""), "laSoNguyen tu choi chuoi rong");
    kiemTra(!laSoNguyen("-1"), "laSoNguyen tu choi so am");

    kiemTra(ganBangDouble(chuoiSangSo("123"), 123.0), "chuoiSangSo chuyen so nguyen");
    kiemTra(ganBangDouble(chuoiSangSo("12.5"), 12.5), "chuoiSangSo chuyen so thuc");
    kiemTra(ganBangDouble(chuoiSangSo(" 007.25 "), 7.25), "chuoiSangSo bo khoang trang");

    string truong[5];
    int soTruong = tachDong("1|Lap trinh|De", truong, 5);
    kiemTra(soTruong == 3 && truong[0] == "1" && truong[1] == "Lap trinh" && truong[2] == "De",
             "tachDong tach dung cac truong");

    vector<int> a = {1, 2, 3, 4, 5};
    xaoTronVectorSoNguyen(a);
    sort(a.begin(), a.end());
    kiemTra(a == vector<int>({1, 2, 3, 4, 5}), "xaoTronVectorSoNguyen giu nguyen tap phan tu");

    kiemTra(ganBangDouble(tinhDiem(8, 10), 8.0), "tinhDiem tinh diem binh thuong");
    kiemTra(ganBangDouble(tinhDiem(0, 10), 0.0), "tinhDiem khi khong dung cau nao");
    kiemTra(ganBangDouble(tinhDiem(5, 0), 0.0), "tinhDiem tranh chia cho 0");
}

void testDuLieuVaTimKiem() {
    khoiTaoDuLieuMau();

    kiemTra(timMonHoc(1) == 0, "timMonHoc tim duoc ma ton tai");
    kiemTra(timMonHoc(99) == -1, "timMonHoc tra ve -1 khi khong ton tai");

    kiemTra(timThiSinh(2) == 1, "timThiSinh tim duoc ma ton tai");
    kiemTra(timThiSinh(99) == -1, "timThiSinh tra ve -1 khi khong ton tai");

    kiemTra(timCauHoi(3) == 2, "timCauHoi tim duoc ma ton tai");
    kiemTra(timCauHoi(99) == -1, "timCauHoi tra ve -1 khi khong ton tai");
}

void testNganHangCauHoi() {
    khoiTaoDuLieuMau();

    kiemTra(sinhMaCauHoiMoi() == 6, "sinhMaCauHoiMoi lay ma lon nhat cong 1");
    kiemTra(laCauHoiDungLoai(dsCauHoi[0], 1, 1), "laCauHoiDungLoai nhan cau de dung mon");
    kiemTra(!laCauHoiDungLoai(dsCauHoi[0], 2, 1), "laCauHoiDungLoai tu choi sai mon");
    kiemTra(laCauHoiDungLoai(dsCauHoi[2], 1, 2), "laCauHoiDungLoai nhan cau kho dung mon");

    kiemTra(demCauHoiTheoMonVaLoai(1, 1) == 2, "demCauHoiTheoMonVaLoai dem cau de");
    kiemTra(demCauHoiTheoMonVaLoai(1, 2) == 2, "demCauHoiTheoMonVaLoai dem cau kho");
    kiemTra(demCauHoiTheoMonVaLoai(2, 2) == 0, "demCauHoiTheoMonVaLoai tra 0 khi khong co cau kho");
}

void testThi() {
    khoiTaoDuLieuMau();
    srand(1);

    vector<CauHoiThi> deThi;
    themCauHoiVaoDeThi(0, deThi);
    kiemTra(static_cast<int>(deThi.size()) == 1, "themCauHoiVaoDeThi them mot cau");
    kiemTra(deThi[0].maCauHoi == 1, "themCauHoiVaoDeThi gan dung ma cau hoi");
    kiemTra(deThi[0].dapAnDaChon == -1, "themCauHoiVaoDeThi mac dinh chua chon dap an");
    kiemTra(laHoanViDapAnHopLe(deThi[0].thuTuDapAn), "themCauHoiVaoDeThi tao hoan vi dap an hop le");

    deThi.clear();
    sinhDeThi(1, 2, 1, deThi);
    kiemTra(static_cast<int>(deThi.size()) == 3, "sinhDeThi sinh dung tong so cau");

    int soCauDe = 0;
    int soCauKho = 0;
    bool tatCaDapAnHopLe = true;
    for (int i = 0; i < static_cast<int>(deThi.size()); i++) {
        int viTri = timCauHoi(deThi[i].maCauHoi);
        if (viTri != -1 && dsCauHoi[viTri].mucDo == 1) soCauDe++;
        if (viTri != -1 && dsCauHoi[viTri].mucDo >= 2) soCauKho++;
        if (!laHoanViDapAnHopLe(deThi[i].thuTuDapAn)) tatCaDapAnHopLe = false;
    }
    kiemTra(soCauDe == 2 && soCauKho == 1, "sinhDeThi dung so cau de va kho");
    kiemTra(tatCaDapAnHopLe, "sinhDeThi moi cau co thu tu dap an hop le");

    time_t hienTai = time(NULL);
    kiemTra(!hetGio(hienTai, 1), "hetGio tra false khi moi bat dau");
    kiemTra(hetGio(hienTai - 61, 1), "hetGio tra true khi da qua gioi han");
}

void testChamDiemVaBaoCao() {
    khoiTaoDuLieuMau();

    vector<CauHoiThi> deThi;

    CauHoiThi c1;
    c1.maCauHoi = 1;
    c1.thuTuDapAn = {0, 1, 2, 3};
    c1.dapAnDaChon = 0;
    deThi.push_back(c1);

    CauHoiThi c2 = c1;
    c2.maCauHoi = 2;
    c2.dapAnDaChon = 3;
    deThi.push_back(c2);

    CauHoiThi c3 = c1;
    c3.maCauHoi = 3;
    c3.dapAnDaChon = -1;
    deThi.push_back(c3);

    CauHoiThi c4 = c1;
    c4.maCauHoi = 4;
    c4.dapAnDaChon = 3;
    deThi.push_back(c4);

    kiemTra(demCauDung(deThi) == 2, "demCauDung dem dung cau dung");
    kiemTra(sinhMaKetQuaMoi() == 9, "sinhMaKetQuaMoi lay ma lon nhat cong 1");
}

void testDocDuLieuTuFileThat() {
    docDuLieu();

    kiemTra(static_cast<int>(dsMonHoc.size()) > 0, "docDuLieu doc duoc data/subjects.txt");
    kiemTra(static_cast<int>(dsCauHoi.size()) > 0, "docDuLieu doc duoc data/questions.txt");
    kiemTra(static_cast<int>(dsThiSinh.size()) > 0, "docDuLieu doc duoc data/candidates.txt");
}

int main() {
    cout << "===== CHAY UNIT TEST TU DONG =====\n";

    testTienIch();
    testDuLieuVaTimKiem();
    testNganHangCauHoi();
    testThi();
    testChamDiemVaBaoCao();
    testDocDuLieuTuFileThat();

    cout << "\nTong so test dat: " << soTestDat << "\n";
    cout << "Tong so test loi: " << soTestLoi << "\n";

    if (soTestLoi == 0) {
        cout << "Ket qua: TAT CA UNIT TEST DEU DAT\n";
        choNguoiDungXemKetQua();
        return 0;
    }

    cout << "Ket qua: CO UNIT TEST BI LOI\n";
    choNguoiDungXemKetQua();
    return 1;
}
