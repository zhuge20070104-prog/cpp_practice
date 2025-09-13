import { wdOpts } from './Consts.js';
import {remote} from 'webdriverio';
import pkg from 'mochawesome/addContext.js'
const addContext = pkg;


let getDriver = async (wd_opts) => {
    return await remote(wd_opts)
}

global.driver = await getDriver(wdOpts)
global.$ = (selector) => driver.$(selector)
global.$$ = (selector) => driver.$$(selector)

let releaseResource = async (driver_) => {
    console.log("releaseResource")
    await driver_.pause(1000)
    await driver_.deleteSession()
}

let screenShot = async function(ctx, driver_, path_) {
    addContext(ctx, path_)
    await driver_.saveScreenshot(path_)
}

let releaseEach = async function(ctx, driver_, path_) {
    if(ctx.currentTest.state !== 'passed') {
        screenShot(ctx, driver_, path_)
    } 
}

export {releaseResource, addContext, screenShot, releaseEach }