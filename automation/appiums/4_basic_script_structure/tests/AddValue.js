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

    it('Email text field add value', async function () {
      await this.login_form.text_add_value()
    });
});
