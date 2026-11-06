# Maintainer: eufjdknasquwy <e0723044@gmail.com>
pkgname=bytepurge
pkgver=0.6.1
pkgrel=1
pkgdesc="A fast utility for Linux to free disk space by cleaning caches of package managers and other applications."
arch=('x86_64')
url="https://github.com/eufjdknasquwy/bytepurge"
license=('MIT')
depends=('gtkmm3' 'nlohmann-json' 'libayatana-appindicator')
makedepends=('cmake' 'ninja')
source=("$pkgname-$pkgver.tar.gz::$url/archive/v$pkgver.tar.gz")
sha256sums=('c85d49df9c5e7fe16cf8dd8d1bc38bb87944b0c683d1854a574056bd22227217')

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