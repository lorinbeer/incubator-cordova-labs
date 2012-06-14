/**
 * Copyright 2012 Adobe Systems Incorporated
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/**
 * Pender
 * small shim allowing Pender Client projects to run on desktop browsers
 */

var Pender = {
    //width of associated canvas
    width : 0,
    //height of associated canvas
    height : 0,
    //count of resources pending load
    "pending" : 0,
    //html5 Canvas element
    canvaselem : null,
    //canvas 2d rendering context
    canvas : null,
    //preloaded texture assets
    images : [],
    //default or expected id of the Canvas element
    canvasDefaultId : "pendercanvas",
    //ready state
    ready : true,

    /**
     *  Initialize Pender
     */
    init : function (canvasid) {
        canvasid = canvasid || this.canvasDefaultId;
        this.canvaselem = document.getElementById(canvasid);
        if (this.canvaselem.getContext) {
            this.canvas = this.canvaselem.getContext("2d");
            this.height = this.canvaselem.height;
            this.width  = this.canvaselem.width;
        } else {
            throw "Error: canvas id \"" +
                  canvasid +
                  "or " +
                  this.canvasDefaultId +
                  " not found or not a canvas";
        }
    },

    /**
     * load image at path
     */
    loadImage : function (path) {
        var i = 0,
            img = null,
            imgcb = null;

        //call back for Image.onload event    
        imgcb = function () {
            if (img !== null) {
                Pender.images[i] = img;
                Pender.pending -= 1;
                if (Pender.pending <= 0) {
                    Pender.ready = true;
                }
            } else {
                throw "Error: image not loaded";
            }
        };
        //push a null placeholder into the array
        this.images.push(null);
        //generate an id from the length of the array
        i = this.images.length - 1;
        //create the new image
        img = new Image();
        //set the ready state to false
        this.ready = false;
        //increment the pending count
        this.pending += 1;
        //set the images callback
        img.onload = imgcb;
        //set the images source
        img.src = path;
        //return the unique id generated
        return i;
    },

    getImage : function (id) {
        var img = null;
        if (this.images.length > id) {
            img = this.images[id];
        }
        return img;
    },

    setInterval : function (func, spf) {
        var self = this;
        setInterval(function () {
            if (self.ready) {
                func();
            }
        },
            spf);
    }
};