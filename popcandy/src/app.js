var GameLayer = cc.Layer.extend({
    mapPanel: null,
    ui: null,

    score: null,
    level: null,
    steps: null,
    limitStep: 0,
    targetScore: 0,

    moving: false,

    ctor: function () {
        this._super();

        var size = cc.winSize;
        var bg = new cc.Sprite("res/bg.jpg");
        this.addChild(bg, 1);
        bg.x = size.width / 2;
        bg.y = size.height / 2;

        var clippingPanel = new cc.ClippingNode();
        this.addChild(clippingPanel, 2);
        this.mapPanel = new cc.Layer();
        this.mapPanel.x = (size.width - Constant.CANDY_WIDTH * Constant.MAP_SIZE) / 2;
        this.mapPanel.y = (size.height - Constant.CANDY_WIDTH * Constant.MAP_SIZE) / 2;
        clippingPanel.addChild(this.mapPanel, 1);

        var stencil = new cc.DrawNode();
        stencil.drawRect(cc.p(this.mapPanel.x, this.mapPanel.y),
            cc.p(this.mapPanel.x + Constant.CANDY_WIDTH * Constant.MAP_SIZE,
            this.mapPanel.y + Constant.CANDY_WIDTH * Constant.MAP_SIZE), cc.color(0, 0, 0), 1, cc.color(0, 0, 0));
        clippingPanel.stencil = stencil;

        this._init();

        this.ui = new GameUI(this);
        this.addChild(this.ui, 3);

        if ("touches" in cc.sys.capabilities) {
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ONE_BY_ONE,
                onTouchBegan: this._onTouchBegan.bind(this)
            }, this.mapPanel);
        } else {
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseDown:this._onMouseDown.bind(this)
            }, this.mapPanel);
        }

        return true;
    },

    _onTouchBegan:function (touch, event) {
        var col = Math.floor((touch.getLocation().x - this.mapPanel.x) / Constant.CANDY_WIDTH);
        var row = Math.floor((touch.getLocation().y - this.mapPanel.y) / Constant.CANDY_WIDTH);
        this._popCandy(col, row);

        return true;
    },

    _onMouseDown:function (event) {
        var col = Math.floor((event.getLocationX() - this.mapPanel.x) / Constant.CANDY_WIDTH);
        var row = Math.floor((event.getLocationY() - this.mapPanel.y) / Constant.CANDY_WIDTH);
        this._popCandy(col, row);
    },

    _popCandy:function (col, row) {
        if (this.moving) return;
        var joinCandys = [this.map[col][row]];
        var index = 0;
        var pushIntoCandys = function (element) {
            if (joinCandys.indexOf(element) < 0) {
                joinCandys.push(element);
            }
        };

        while (index < joinCandys.length) {
            var candy = joinCandys[index];
            if (this._checkCandyExist(candy.column - 1, candy.row) && this.map[candy.column - 1][candy.row].type == candy.type) {
                pushIntoCandys(this.map[candy.column - 1][candy.row]);
            }
            if (this._checkCandyExist(candy.column + 1, candy.row) && this.map[candy.column + 1][candy.row].type == candy.type) {
                pushIntoCandys(this.map[candy.column + 1][candy.row]);
            }
            if (this._checkCandyExist(candy.column, candy.row - 1) && this.map[candy.column][candy.row - 1].type == candy.type) {
                pushIntoCandys(this.map[candy.column][candy.row - 1]);
            }
            if (this._checkCandyExist(candy.column, candy.row + 1) && this.map[candy.column][candy.row + 1].type == candy.type) {
                pushIntoCandys(this.map[candy.column][candy.row + 1]);
            }
            index++;
        }

        if (joinCandys.length <= 1)
            return;

        this.steps++;
        this.moving = true;

        for (var i = 0; i < joinCandys.length; i++) {
            var candy = joinCandys[i];
            this.mapPanel.removeChild(candy);
            this.map[candy.column][candy.row] = null;
        }

        this.score += joinCandys.length * joinCandys.length;
        this._generateNewCandy();
        this._checkSucceedOrFail();
    },
    _checkCandyExist: function(i, j){
        if(i >= 0 && i < Constant.MAP_SIZE && j >= 0 && j < Constant.MAP_SIZE){
            return true;
        }
        return false;
    },

    _generateNewCandy: function () {
        var maxTime = 0;
        for (var i = 0; i < Constant.MAP_SIZE; i++) {        //deal each column
            var missCount = 0;
            for (var j = 0; j < this.map[i].length; j++) {

                var candy = this.map[i][j];
                if(!candy){
                    var candy = Candy.createRandomType(i,Constant.MAP_SIZE+missCount);
                    this.mapPanel.addChild(candy);
                    candy.x = candy.column * Constant.CANDY_WIDTH + Constant.CANDY_WIDTH/2;
                    candy.y = candy.row * Constant.CANDY_WIDTH + Constant.CANDY_WIDTH/2;
                    this.map[i][candy.row] = candy;
                    missCount++;
                }else{
                    var fallLength = missCount;
                    if(fallLength > 0){
                        var duration = Math.sqrt(2*fallLength/Constant.FALL_ACCELERATION);
                        if(duration > maxTime)
                            maxTime = duration;
                        var move = cc.moveTo(duration, candy.x, candy.y-Constant.CANDY_WIDTH*fallLength).easing(cc.easeIn(2));    //easeIn参数是幂，以几次幂加速
                        candy.runAction(move);
                        candy.row -= fallLength;        //adjust all candy's row
                        this.map[i][j] = null;
                        this.map[i][candy.row] = candy;
                    }
                }
            }

            //移除超出地图的临时元素位置
            for (var j = this.map[i].length; j >= Constant.MAP_SIZE; j--) {
                this.map[i].splice(j, 1);
            }
        }
        this.scheduleOnce(this._finishCandyFalls.bind(this), maxTime);
    },

    _finishCandyFalls: function () {
        this.moving = false;
    },

    _checkSucceedOrFail: function () {
        if(this.score > this.targetScore){
            this.ui.showSuccess();
            this.score += (this.limitStep - this.steps) * 30;
            Storage.setCurrentLevel(this.level+1);
            Storage.setCurrentScore(this.score);
            this.scheduleOnce(function(){
                cc.director.runScene(new GameScene());
            }, 3);
        }else if(this.steps >= this.limitStep){
            this.ui.showFail();
            Storage.setCurrentLevel(0);
            Storage.setCurrentScore(0);
            this.scheduleOnce(function(){
                cc.director.runScene(new GameScene());
            }, 3);
        }
    },
    _init: function () {
        this.steps = 0;
        this.level = Storage.getCurrentLevel();
        this.score = Storage.getCurrentScore();
        this.limitStep = Constant.levels[this.level].limitStep;
        this.targetScore = Constant.levels[this.level].targetScore;

        this.map = [];
        for (var i = 0; i < Constant.MAP_SIZE; i++) {
            var col = [];
            for (var j = 0; j < Constant.MAP_SIZE; j++) {
                var candy = Candy.createRandomType(i, j);
                this.mapPanel.addChild(candy);
                candy.x = i * Constant.CANDY_WIDTH + Constant.CANDY_WIDTH / 2;
                candy.y = j * Constant.CANDY_WIDTH + Constant.CANDY_WIDTH / 2;
                col.push(candy);
            }
            this.map.push(col);
        }
    }
});

var GameScene = cc.Scene.extend({
    onEnter: function () {
        this._super();
        var layer = new GameLayer();
        this.addChild(layer);
    }
});


