import { test } from 'node:test';
import assert from 'node:assert/strict';
import { applyYue2StyleTemplate } from './style.js';

// #238: the create path prefixes "<trigger>, " before YuE2 adds its own opener.
test('strips a bare leading "<trigger>," before composing', () => {
  assert.equal(applyYue2StyleTemplate({ trigger: 't', caption: 't, rock' }), 't, in the style of t. rock');
});

test('bare trigger strip is case-insensitive', () => {
  assert.equal(applyYue2StyleTemplate({ trigger: 't', caption: 'T, rock' }), 't, in the style of t. rock');
});

test('a trigger that only prefixes a longer word is kept', () => {
  assert.equal(applyYue2StyleTemplate({ trigger: 't', caption: 'tango, rock' }), 't, in the style of t. tango, rock');
});

test('full opener and bare prefix together collapse to one opener', () => {
  assert.equal(
    applyYue2StyleTemplate({ trigger: 't', caption: 't, in the style of t. t, rock' }),
    't, in the style of t. rock',
  );
});

test('stays idempotent', () => {
  const once = applyYue2StyleTemplate({ trigger: 't', caption: 't, rock' });
  assert.equal(applyYue2StyleTemplate({ trigger: 't', caption: once }), once);
});
