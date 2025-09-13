import { releaseResource } from '../utils/Func.js';

describe('Learning WebdriverIO API',  () => {
    after(async () => {
      await releaseResource(driver)
    })

    it('Email text field add value', async  () => {
      const LOGIN_ICON_HOME_SCREEN = '~Login'
      const EMAIL_TEXT_FIELD = '~input-email'
      await $(LOGIN_ICON_HOME_SCREEN).then((ele) => ele.click())
      let email_text_field = await $(EMAIL_TEXT_FIELD)
      email_text_field.addValue("a@")
      email_text_field.addValue("a.com")

      await driver.pause(2000)
      email_text_field.setValue("new@a.com")
      await driver.pause(2000)
      email_text_field.clearValue()
      await driver.pause(3000)
    });
});
