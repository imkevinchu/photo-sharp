function reload() {

   document.images['photo#'].src = './outputs/testing.jpg?' + Math.floor(Math.random() * 2000);
   document.images['photo'].src = './outputs/testing1.jpg?' + Math.floor(Math.random() * 2000);

   timeout = setTimeout('reload()', 500);
}
