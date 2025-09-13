import { wdOpts } from './Consts.js';
import {remote} from 'webdriverio';


let getDriver = async function() {
    return await remote(wdOpts)
}


let releaseResource = async function(driver) {
    console.log("releaseResource")
    await driver.pause(1000)
    await driver.deleteSession()
}

export {getDriver, releaseResource}