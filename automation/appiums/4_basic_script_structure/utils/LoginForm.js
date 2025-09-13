

const LOGIN_ICON_HOME_SCREEN = '~Login'
const EMAIL_TEXT_FIELD = '~input-email'
const PASSWORD_TEXT_FIELD = '~input-password'
const LOGIN_BTN = '~button-LOGIN'

const FORM_ICON_HOME_SCREEN = '~Forms'
const TEXT_INPUT_FIELD = '~text-input'
const INPUT_TEXT_RESULT = '~input-text-result'
const SWITCH_BTN='~switch'


class LoginForm {
    constructor(driver) {
        this.driver = driver
    }
    async go_to_login_page() { 
        const login_item = await this.driver.$('~Login');
        await login_item.click();
    }

    async go_to_login_page_xpath() { 
        const login_item = await this.driver.$('//android.widget.TextView[@text="Login"]');
        await login_item.click();
    }

    async login() {
        await this.driver.$(LOGIN_ICON_HOME_SCREEN).then( async function(ele) {ele.click()});
        
        await this.driver.$(EMAIL_TEXT_FIELD).then
        (async function(ele) {ele.setValue('a@a.com')});
        
        await this.driver.$(PASSWORD_TEXT_FIELD).then
        (async function(ele) {ele.setValue('12345678')});
        
        await this.driver.$(LOGIN_BTN).then( async function(ele) {ele.click()});

        await this.driver.pause(3000)
    }

    async text_add_value() {
        await this.driver.$(LOGIN_ICON_HOME_SCREEN).then(
            async function(ele) {ele.click();}
        );
        
        let email_text_field = await this.driver.$(EMAIL_TEXT_FIELD);
        email_text_field.addValue("a@")
        email_text_field.addValue("a.com")
        
        await this.driver.pause(2000)

        email_text_field.setValue("new@a.com")

        await this.driver.pause(2000)

        email_text_field.clearValue()

        await this.driver.pause(3000)
    }

    async get_textview_text() {
        await this.driver.$(FORM_ICON_HOME_SCREEN).then(
            async function(ele) {ele.click();}
        );

        await this.driver.$(TEXT_INPUT_FIELD).then(async function(ele) {
            ele.setValue('abc')
        })

        let text = await this.driver.$(INPUT_TEXT_RESULT).then(async function(ele) {
            return ele.getText()
        })

        console.log('Input text: ', text)
        await this.driver.pause(3000)
    }

    async hit_toggle_button() {
        await this.driver.$(FORM_ICON_HOME_SCREEN).then(
            async function(ele) {ele.click();}
        );
        
        await this.driver.$(SWITCH_BTN).then(async (ele)=>{
            ele.click()
        });

        await this.driver.pause(3000);
    }

    async wait_for_displayed() {
        await this.driver.$(LOGIN_ICON_HOME_SCREEN).then(
            async function(ele) {ele.click();}
        );

        await this.driver.$(SWITCH_BTN).then((ele) => ele.waitForDisplayed({timeout: 8000}))
        await this.driver.$(SWITCH_BTN).then((ele)=>{
            ele.click()
        });

        await this.driver.pause(3000);
    }

    async take_screen_shot() {
        await this.driver.$(FORM_ICON_HOME_SCREEN).then(
            async function(ele) {ele.click();}
        );
        
        await this.driver.$(SWITCH_BTN).then(async (ele) => {
            ele.waitForDisplayed()
        })

        await this.driver.saveScreenshot("./screenshot/whole.png");

        await this.driver.$(SWITCH_BTN).then(async (ele)=>{
            ele.click()
        });

        await this.driver.$(SWITCH_BTN).then(async (ele) => {
            ele.saveScreenshot("./screenshot/switch_button.png")
        });
        
        await this.driver.pause(3000);
    }
}


export {LoginForm}