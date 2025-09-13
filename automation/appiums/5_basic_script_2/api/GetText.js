import { releaseResource } from '../utils/Func.js';

describe('Learning WebdriverIO API', () => {
  
    after(async () => {
      await releaseResource(driver)
    })

    it('should login successfully', async () => {
      const FORM_ICON_HOME_SCREEN = '~Forms'
      const TEXT_INPUT_FIELD = '~text-input'
      const INPUT_TEXT_RESULT = '~input-text-result'

      await $(FORM_ICON_HOME_SCREEN).then(
          (ele) => {ele.click()}
      );

      await $(TEXT_INPUT_FIELD).then((ele) => {
          ele.setValue('abc')
      })
      
      await $(INPUT_TEXT_RESULT).
        then((ele) => ele.waitForDisplayed({timeout: 6000}))
      
      let text = await $(INPUT_TEXT_RESULT).then((ele) => {
          return ele.getText()
      })

      console.log('Input text: ', text)
      await driver.pause(3000)
    })
});
