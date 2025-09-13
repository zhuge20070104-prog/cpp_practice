import { LoginForm } from '../utils/LoginForm.js';
import { getDriver, releaseResource } from '../utils/Func.js';

describe('Learning WebdriverIO API', function () {
    before(async function () {
      this.driver = await getDriver()
      this.login_form = new LoginForm(this.driver)
    })

    after(async function () {
      await releaseResource(this.driver)
    })

    it('should click on Login Icon successfully', async function () {
      await this.login_form.go_to_login_page_xpath() 
    });
});
