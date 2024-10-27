#include <bits/stdc++.h>
using namespace std;

// Lớp ChứcVu (Chức vụ)
class ChucVu {
private:
    int maSo;
    string ten;
    double luongCoBan;

public:
    ChucVu(int maSo, const string& ten, double luongCoBan)
        : maSo(maSo), ten(ten), luongCoBan(luongCoBan) {}

    double layLuongCoBan() const {
        return luongCoBan;
    }

    string layTenChucVu() const {
        return ten;
    }
};

class PhongBan; // Khai báo trước

// Lớp NhanVien (Nhân viên)
class NhanVien {
private:
    int maSo;
    string ten;
    int tuoi;
    ChucVu chucVu;
    PhongBan* phongBan; // Con trỏ tới phòng ban
    double luong;
    int chamCong;

public:
    NhanVien(int maSo, const string& ten, int tuoi, const ChucVu& chucVu, PhongBan* pb)
        : maSo(maSo), ten(ten), tuoi(tuoi), chucVu(chucVu), phongBan(pb), luong(0), chamCong(0) {}

    void danhDauChamCong(int soNgay) {
        chamCong = soNgay;
    }

    void tinhLuong() {
        luong = chucVu.layLuongCoBan() * (chamCong / 30.0); // Giả định 30 ngày làm việc
    }

    void hienThiThongTin() const; // Chỉ khai báo, định nghĩa sẽ ở dưới
};

// Lớp PhongBan (Phòng ban)
class PhongBan {
private:
    int maSo;
    string ten;
    vector<NhanVien*> danhSachNhanVien; // Sử dụng con trỏ để quản lý nhân viên

public:
    PhongBan(int maSo, const string& ten) : maSo(maSo), ten(ten) {}

    void themNhanVien(NhanVien* nhanVien) {
        danhSachNhanVien.push_back(nhanVien);
    }

    void hienThiNhanVien() const {
        cout << "Nhân viên trong phòng " << ten << ":\n";
        for (const auto& nv : danhSachNhanVien) {
            nv->hienThiThongTin();
        }
    }

    string layTenPhongBan() const {
        return ten;
    }
};

// Định nghĩa hàm hienThiThongTin() của NhanVien sau khi PhongBan đã được định nghĩa đầy đủ
void NhanVien::hienThiThongTin() const {
    cout << "Mã: " << maSo << ", Tên: " << ten << ", Tuổi: " << tuoi
         << ", Chức vụ: " << chucVu.layTenChucVu()
         << ", Phòng ban: " << phongBan->layTenPhongBan()
         << ", Lương: " << luong << "\n";
}

// Lớp DanhGia (Đánh giá)
class DanhGia {
private:
    int diem;
    string nhanXet;

public:
    DanhGia(int diem, const string& nhanXet)
        : diem(diem), nhanXet(nhanXet) {}

    void hienThiDanhGia() const {
        cout << "Điểm: " << diem << "/10, Nhận xét: " << nhanXet << "\n";
    }
};

// Lớp SoDoToChuc (Sơ đồ tổ chức)
class SoDoToChuc {
private:
    map<PhongBan*, vector<NhanVien*>> soDo;

public:
    void themVaoSoDo(PhongBan* pb, NhanVien* nv) {
        soDo[pb].push_back(nv);
    }

    void hienThiSoDo() const {
        for (const auto& muc : soDo) {
            cout << "Phòng ban: " << muc.first->layTenPhongBan() << "\n";
            for (const auto& nv : muc.second) {
                nv->hienThiThongTin();
            }
            cout << "-----------------------------------\n";
        }
    }
};

// Chương trình chính
int main() {
    // Tạo các đối tượng chức vụ
    ChucVu quanLy(1, "Quản lý", 5000);
    ChucVu lapTrinhVien(2, "Lập trình viên", 3000);

    // Tạo đối tượng phòng ban
    PhongBan phongCNTT(1, "Phòng Công nghệ Thông tin");
    PhongBan phongNS(2, "Phòng Nhân sự");

    // Tạo các nhân viên
    NhanVien nv1(1, "Nguyễn Văn A", 30, quanLy, &phongCNTT);
    NhanVien nv2(2, "Lê Thị B", 25, lapTrinhVien, &phongCNTT);
    NhanVien nv3(3, "Trần Văn C", 28, lapTrinhVien, &phongNS);

    // Thêm nhân viên vào phòng ban
    phongCNTT.themNhanVien(&nv1);
    phongCNTT.themNhanVien(&nv2);
    phongNS.themNhanVien(&nv3);

    // Chấm công và tính lương
    nv1.danhDauChamCong(28);
    nv1.tinhLuong();

    nv2.danhDauChamCong(30);
    nv2.tinhLuong();

    nv3.danhDauChamCong(27);
    nv3.tinhLuong();

    // Tạo hệ thống đánh giá nhân viên
    DanhGia danhGia1(8, "Hiệu suất tốt");
    DanhGia danhGia2(9, "Hiệu suất xuất sắc");

    // Hiển thị đánh giá
    cout << "\nĐánh giá cho Nhân viên 1:\n";
    danhGia1.hienThiDanhGia();
    cout << "\nĐánh giá cho Nhân viên 2:\n";
    danhGia2.hienThiDanhGia();

    // Hiển thị thông tin nhân viên trong từng phòng ban
    cout << "\n--- Thông tin Phòng ban ---\n";
    phongCNTT.hienThiNhanVien();
    phongNS.hienThiNhanVien();

    // Xây dựng và hiển thị sơ đồ tổ chức
    SoDoToChuc soDoToChuc;
    soDoToChuc.themVaoSoDo(&phongCNTT, &nv1);
    soDoToChuc.themVaoSoDo(&phongCNTT, &nv2);
    soDoToChuc.themVaoSoDo(&phongNS, &nv3);

    cout << "\n--- Sơ đồ Tổ chức ---\n";
    soDoToChuc.hienThiSoDo();

    return 0;
}
