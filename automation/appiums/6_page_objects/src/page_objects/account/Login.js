import { expect } from "chai";

const LOGIN_ICON_HOME_SCREEN = '~Login'
const EMAIL_TEXT_FIELD = '~input-email'
const PASSWORD_TEXT_FIELD = '~input-password'
const LOGIN_BTN = '~button-LOGIN'
const SUCCESS_MSG = '//android.widget.TextView[@resource-id="android:id/message"]'

class Login {
    async is_on_home_page() {
        await $(LOGIN_ICON_HOME_SCREEN).then(async ele => await ele.waitForDisplayed())
        return await $(LOGIN_ICON_HOME_SCREEN).then(async ele => await ele.isDisplayed())
    }

    async go_to_login_page() {
        await $(LOGIN_ICON_HOME_SCREEN).then(async ele => await ele.click())
        await $(LOGIN_BTN).then(async ele => await ele.waitForDisplayed())
        return await $(LOGIN_BTN).then(async ele => await ele.isDisplayed())
    }
    

    async login() {
        await $(EMAIL_TEXT_FIELD).then(async ele => await ele.setValue('a@a.com'))
        await $(PASSWORD_TEXT_FIELD).then(async ele => await ele.setValue('12345678'))
        await $(LOGIN_BTN).then(async ele => await ele.click())
    }

    async is_login_successful() {
        await $(SUCCESS_MSG).then(async ele => await ele.waitForDisplayed())
        let text = await $(SUCCESS_MSG).then(async ele => await ele.getText())
        console.log("Text is: " + text)
        expect(text).to.equal("You are logged in!!")
        return true
    }
}

export {Login}