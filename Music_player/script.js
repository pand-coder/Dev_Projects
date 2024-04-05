document.addEventListener('DOMContentLoaded', function () {
  var imagePaths = [
      'han_demon.jpg',
      'han_ram.png',
      'hanbg.jpg',
      'han.jpg'
  ];

  var currentIndex = 0;

  function changeBackground() {
      document.querySelector('.container').style.backgroundImage = 'url("' + imagePaths[currentIndex] + '")';
      currentIndex = (currentIndex + 1) % imagePaths.length;
  }

  // Change background every 5 seconds (5000 milliseconds)
  setInterval(changeBackground, 2000); // Change every 2 seconds for demonstration purposes
});
