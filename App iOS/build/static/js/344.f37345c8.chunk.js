/*! For license information please see 344.f37345c8.chunk.js.LICENSE.txt */
"use strict";(globalThis.webpackChunkionic_app_base=globalThis.webpackChunkionic_app_base||[]).push([[344],{344:(e,t,o)=>{o.r(t),o.d(t,{startTapClick:()=>i});var n=o(811);const i=e=>{let t,o,i,v=10*-u,p=0;const f=e.getBoolean("animated",!0)&&e.getBoolean("rippleEffect",!0),h=new WeakMap,m=e=>{v=(0,n.v)(e),b(e)},L=()=>{i&&clearTimeout(i),i=void 0,t&&(k(!1),t=void 0)},w=e=>{t||E(s(e),e)},b=e=>{E(void 0,e)},E=(e,o)=>{if(e&&e===t)return;i&&clearTimeout(i),i=void 0;const{x:s,y:c}=(0,n.u)(o);if(t){if(h.has(t))throw new Error("internal error");t.classList.contains(r)||T(t,s,c),k(!0)}if(e){const t=h.get(e);t&&(clearTimeout(t),h.delete(e)),e.classList.remove(r);const o=()=>{T(e,s,c),i=void 0};a(e)?o():i=setTimeout(o,d)}t=e},T=(e,t,n)=>{if(p=Date.now(),e.classList.add(r),!f)return;const i=c(e);null!==i&&(g(),o=i.addRipple(t,n))},g=()=>{void 0!==o&&(o.then((e=>e())),o=void 0)},k=e=>{g();const o=t;if(!o)return;const n=l-Date.now()+p;if(e&&n>0&&!a(o)){const e=setTimeout((()=>{o.classList.remove(r),h.delete(o)}),l);h.set(o,e)}else o.classList.remove(r)},C=document;C.addEventListener("ionGestureCaptured",L),C.addEventListener("touchstart",(e=>{v=(0,n.v)(e),w(e)}),!0),C.addEventListener("touchcancel",m,!0),C.addEventListener("touchend",m,!0),C.addEventListener("pointercancel",L,!0),C.addEventListener("mousedown",(e=>{if(2===e.button)return;const t=(0,n.v)(e)-u;v<t&&w(e)}),!0),C.addEventListener("mouseup",(e=>{const t=(0,n.v)(e)-u;v<t&&b(e)}),!0)},s=e=>{if(void 0===e.composedPath)return e.target.closest(".ion-activatable");{const t=e.composedPath();for(let e=0;e<t.length-2;e++){const o=t[e];if(!(o instanceof ShadowRoot)&&o.classList.contains("ion-activatable"))return o}}},a=e=>e.classList.contains("ion-activatable-instant"),c=e=>{if(e.shadowRoot){const t=e.shadowRoot.querySelector("ion-ripple-effect");if(t)return t}return e.querySelector("ion-ripple-effect")},r="ion-activated",d=100,l=150,u=2500}}]);
//# sourceMappingURL=344.f37345c8.chunk.js.map