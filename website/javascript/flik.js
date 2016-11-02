var positions = [];

var pieceTypes = ["red", "green", "yellow", "blue"];

var world = null;

var pieces = [];

var Piece = function(color, position, size) {
  this.color = color;
  this.position = position;

  this.velocity = {
    x: ((Math.random() * 100) + 20) * (Math.random() > 0.5 ? 1 : -1),
    y: ((Math.random() * 100) + 20) * (Math.random() > 0.5 ? 1 : -1)
  };

  var image = new Image();
  image.src = "image/" + color + ".png";
  image.style.position = "absolute";
  image.style.top = position.y + "px";
  image.style.left = position.x + "px";
  image.style.transform = "scale(" + (size * 0.25) +")";
  this.element = image;

  $("#pieces").append(image);
};

Piece.prototype.update = function(deltaMillis) {
  this.position.x += this.velocity.x * deltaMillis;
  this.position.y += this.velocity.x * deltaMillis;

  this.element.style.top = this.position.y + "px";
  this.element.style.left = this.position.x + "px";
};

$(document).ready(function() {
  var numPieces = 6;

  var content = $("#content");

  for (var i = 0; i < numPieces; i++) {
    var type = pieceTypes[i%pieceTypes.length];
    addPiece(type);
  }

  requestAnimationFrame(onFrame);
});

var lastTime = 0;

function onFrame(time) {
  var delta = (time - lastTime) / 1000;
  lastTime = time;

  for (var i = 0; i < pieces.length; i++) {
    pieces[i].update(delta);
  }

  requestAnimationFrame(onFrame);
}

function randomPosition() {
  var content = $(".content");
  var x = Math.random() * content.width() * 0.8;
  var y = Math.random() * content.height() * 0.5;

  return { x: x, y: y }
}

function randomScale() {
  return ((Math.random() * 0.7) + 0.3);
}

function randomPiece() {
  var type = Math.floor(Math.random() * 4);
  return pieceTypes[type];
}

function addPiece(type) {
  var position = randomPosition();
  for (var j = 0; j < positions.length; j++) {
    if (distance(position, position[j] < 200)) {
      position = randomPosition();
      j = 0;
    }
  }

  var size = randomScale();
  var piece = new Piece(type, position, size);
  pieces.push(piece);
}

function distance(p1, p2) {
  var dx = p2.x - p1.x;
  var dy = p2.y - p1.y;
  return Math.sqrt((dx*dx) + (dy*dy));
}