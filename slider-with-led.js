var five = require('johnny-five');
var board = new five.Board();

board.on('ready', function() {

  var slider = new five.Sensor('A0');
  var led = new five.Led(13);

  // the slider range [0, 100] is logaritmic, 
  // so around 0.5 you should be in the middle of 
  // the physical slider 
  slider.scale([0, 100]).on('slide', function() {

  	if (this.value > 0.5) {
      led.on();
      console.log('on:', this.value);
  	} else {
      led.off();
      console.log('off:', this.value);
    }
  });
});