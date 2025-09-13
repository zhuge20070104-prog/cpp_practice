const capabilities = {
    "platformName": "Android",
    "appium:automationName": "UiAutomator2",
    "appium:udid": "R28M32MWVBH",
    "appium:appPackage": "com.wdiodemoapp",
    "appium:appActivity": ".MainActivity",
    // "appium:noReset": true
}

const wdOpts = {
    hostname: process.env.APPIUM_HOST || 'localhost',
    path: "/wd/hub",
    port: parseInt(process.env.APPIUM_PORT, 10) || 4723,
    logLevel: 'info',
    capabilities,
};

export {capabilities, wdOpts}