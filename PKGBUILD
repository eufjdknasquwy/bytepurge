# Maintainer: eufjdknasquwy <e0723044@gmail.com>
pkgname=bytepurge
pkgver=0.5.0
pkgrel=1
pkgdesc="A utility for Linux to free disk space by cleaning caches of package managers and other caches"
arch=('x86_64')
url="https://github.com/eufjdknasquwy/bytepurge"
license=('MIT')
depends=('gtkmm3' 'nlohmann-json' 'libayatana-appindicator')
makedepends=('cmake' 'ninja')
source=("$pkgname-$pkgver.tar.gz::$url/archive/v$pkgver.tar.gz")
sha256sums=('8fc67a5ddc29f9a06cdad59f10bb2db0075f4dbd8d102360e39f15480ed31868')

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