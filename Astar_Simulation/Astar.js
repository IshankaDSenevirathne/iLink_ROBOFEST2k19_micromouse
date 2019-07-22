var cols=5;
var rows=5;
var grid=new Array(cols);
function setup(){
    createCanvas(400,400);
    console.log('A*');

    for(var i=0;i<cols;i++){
        grid[i]=new Array(rows);
    }
    console.log(grid);
}
function draw(){
    background(0);
}