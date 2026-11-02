# Maintainer: eufjdknasquwy <e0723044@gmail.com>
pkgname=bytepurge
pkgver=0.5.1
pkgrel=1
pkgdesc="A utility for Linux to free disk space by cleaning caches of package managers and other caches"
arch=('x86_64')
url="https://github.com/eufjdknasquwy/bytepurge"
license=('MIT')
depends=('gtkmm3' 'nlohmann-json' 'libayatana-appindicator')
makedepends=('cmake' 'ninja')
source=("$pkgname-$pkgver.tar.gz::$url/archive/v$pkgver.tar.gz")
sha256sums=('a61be6762981453160b54e9dda7282201122df7abea9c3d5bf2472cc0a9b862b')

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