function reload() {

   document.images['photo#'].src = '/Users/k4vglitcher/Desktop/photo-sharp/outputs/testing.jpg?' + Math.floor(Math.random() * 2000);

   timeout = setTimeout('reload()', 1000);
}
