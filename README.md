# 👵🏼 Yaşlılar İçin Hatırlatma ve Yardım Asistanı

Bu proje, yaşlı bireylerin günlük hayatlarını kolaylaştırmak amacıyla tasarlanmış, **kullanıcı dostu, tuş takımı ile yönetilen**, sesli ve görsel uyarı sistemine sahip bir **hatırlatma ve yardım asistanıdır**.

## 🎯 Amaç

İlaç saatlerini, yemek zamanlarını ve acil yardım ihtiyaçlarını kolayca hatırlatmak ve gerektiğinde servo motor ile fiziksel etkileşim sağlamak.

---

## 🛠 Kullanılan Donanım

- ✅ **Arduino Mega 2560**
- ✅ **4x4 Tuş Takımı (Keypad)**
- ✅ **16x2 I2C LCD Ekran**
- ✅ **Buzzer**
- ✅ **Sarı / Yeşil / Kırmızı LED**
- ✅ **Servo Motor (SG90 veya eşdeğeri)**
- 🔌 Breadboard, jumper kablolar

---

## 📋 Özellikler

| Tuş | Görev                      | Açıklama                                     |
|-----|----------------------------|----------------------------------------------|
| `1` | 💊 İlaç Hatırlatma         | Sarı LED + Sesli Uyarı + LCD mesajı          |
| `2` | 🍽️ Yemek Zamanı Uyarısı   | Yeşil LED + Sesli Uyarı + LCD mesajı         |

| `3` | 🚨 Yardım Çağrısı          | Kırmızı LED + Uzun Alarm + LCD uyarısı       |
| `A` | ✨ Servo Motor Kontrolü    | İlaç kutusu açma hareketi                    |
| `*` | 🔄 Ekran Temizleme         | LCD ekran sıfırlanır                         |
| `#` | 🔁 Ana Menüye Dönüş        | Ana karşılama mesajı gösterilir              |

---

## 💡 Nasıl Çalışır?

1. Kullanıcı istediği fonksiyonu tuş takımından seçer.
2. LCD ekran, tuşun işlevine göre mesaj gösterir.
3. Buzzer ve LED yardımıyla uyarı verilir.
4. `A` tuşuna basıldığında servo motor kutuyu açar.

---

## 📷 Görseller (isteğe bağlı)

> ![yasli_bakim_1](https://github.com/user-attachments/assets/1a4192cc-ee4f-4ac8-a3b0-29467d6b8551)
> ![yasli_bakim_2](https://github.com/user-attachments/assets/e816c67a-a0a7-4861-a5ee-08d640224ebe)

---

## 🔒 Neden RFID Yok?

Başta RFID entegrasyonu planlanmıştı, ancak modülün kartlarla uyum sorunu nedeniyle sistemden çıkarılmıştır. Güvenlik ihtiyacı duyulursa şifreli menü veya başka doğrulama yöntemleri entegre edilebilir.
lakin siz ikleyebilirsiniz, ilerki süreçlerde ben de ekleyeceğim.

---

## 🧠 Geliştirici Notları

- Bu proje, Arduino programlama, giriş/çıkış kontrolü, donanım senkronizasyonu gibi konularda **uygulamalı bir deneyim sunar.**
- Sistem, yaşlılara yönelik tasarlandığı için **basit, anlaşılır ve doğrudan tepki veren** bir yapı hedeflenmiştir.

---

## 👩‍💻 Geliştiren

**[HALİD UĞUR]** – Bilgisayar Mühendisliği Öğrencisi   
GitHub: [@halidugur]([https://github.com/halidugur])

---

## 📌 Lisans

Bu proje eğitim ve kişisel kullanım amaçlıdır.  
Ticari kullanımlarda kaynak gösterilmesi rica olunur.
