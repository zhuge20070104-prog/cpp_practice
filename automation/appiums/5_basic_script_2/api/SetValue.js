import { releaseResource } from '../utils/Func.js';

describe('Learning WebdriverIO API', function () {
   
    after(async () => {
      await releaseResource(driver)
    })

    it('should login successfully', async () => {
      const LOGIN_ICON_HOME_SCREEN = '~Login'
      const EMAIL_TEXT_FIELD = '~input-email'
      const PASSWORD_TEXT_FIELD = '~input-password'
      const LOGIN_BTN = '~button-LOGIN'
      await $(LOGIN_ICON_HOME_SCREEN).then(
          async (ele) => {await ele.click()});
        
      await $(EMAIL_TEXT_FIELD).then(
          async (ele) => {await ele.setValue('a@a.com')})
      
      await $(PASSWORD_TEXT_FIELD).then
      (async (ele) => {await ele.setValue('12345678')});
      
      await $(LOGIN_BTN).then(async (ele) => { await ele.click()});

      await driver.pause(3000)
    });
});
