var positions = [];

var pieceTypes = ["red", "green", "yellow", "blue"];

var world = null;

$(document).ready(function() {
  var numPieces = 6;

  var content = $("#content");

  world = World.create({
    gravity: { x: 0, y: 0, scale: 0 },
    bounds: {
      min: { x: 0, y: 0 },
      max: { x: content.width(), y: content.height() }
    }
  });

  Bodies.

  for (var i = 0; i < numPieces; i++) {
    var type = pieceTypes[i%pieceTypes.length];
    addPiece(type);
  }
});

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
  var piece = new Image();
  piece.src = "image/" + type + ".png";
  piece.style.position = "absolute";
  piece.style.top = position.y + "px";
  piece.style.left = position.x + "px";
  piece.style.transform = "scale(" + (size * 0.25) +")";

  $("#pieces").append(piece);
}

function distance(p1, p2) {
  var dx = p2.x - p1.x;
  var dy = p2.y - p1.y;
  return Math.sqrt((dx*dx) + (dy*dy));
}