import { releaseResource, addContext, releaseEach } from '../../utils/Func.js';
import { Login } from '../../page_objects/account/Login.js';

describe('Learning WebdriverIO API', () => {
    after(async function() {
      await releaseResource(driver)
    })

    afterEach(async function() {
      await releaseEach(this, driver, './screenshot/login.png')
    })

    it('should click on Login Icon successfully', async function () {
      let login = new Login()
      await login.is_on_home_page()
      addContext(this, 'Go to home page successfully')
      await login.go_to_login_page()
      addContext(this, 'Go to login page successfully')
      await login.login()
      addContext(this, 'Login')
      await login.is_login_successful()
      addContext(this, 'Login successfully')
    });
});
