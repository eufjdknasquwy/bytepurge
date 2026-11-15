# Maintainer: eufjdknasquwy <e0723044@gmail.com>
pkgname=bytepurge
pkgver=0.6.2
pkgrel=1
pkgdesc="A fast utility for Linux to free disk space by cleaning caches of package managers and other applications."
arch=('x86_64')
url="https://github.com/eufjdknasquwy/bytepurge"
license=('MIT')
depends=('gtkmm3' 'nlohmann-json' 'libayatana-appindicator')
makedepends=('cmake' 'ninja')
source=("$pkgname-$pkgver.tar.gz::$url/archive/v$pkgver.tar.gz")
sha256sums=('60e9af7a6da7a7ce2df98a731aa33d26b5f3bce3424f1c6b45fc3d0de1369698')

build() {
  cmake -S "bytepurge-$pkgver" -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/usr \
    -DCMAKE_SKIP_RPATH=ON
  cmake --build build
}

package() {
  DESTDIR="$pkgdir" cmake --install build
}