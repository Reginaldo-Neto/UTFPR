// Copyright (c) Jupyter Development Team.
// Distributed under the terms of the Modified BSD License.

import {
  JupyterFrontEnd,
  JupyterFrontEndPlugin
} from '@jupyterlab/application';

import { PageConfig, PathExt } from '@jupyterlab/coreutils';

import { IDocumentManager } from '@jupyterlab/docmanager';

import { IDocumentWidget, DocumentRegistry } from '@jupyterlab/docregistry';

import { Kernel } from '@jupyterlab/services';

/**
 * A plugin to open document in a new browser tab.
 *
 * TODO: remove and use a custom doc manager?
 */
const opener: JupyterFrontEndPlugin<void> = {
  id: '@jupyter-notebook/docmanager-extension:opener',
  requires: [IDocumentManager],
  autoStart: true,
  activate: (app: JupyterFrontEnd, docManager: IDocumentManager) => {
    const baseUrl = PageConfig.getBaseUrl();

    // patch the `docManager.open` option to prevent the default behavior
    const docOpen = docManager.open;
    docManager.open = (
      path: string,
      widgetName = 'default',
      kernel?: Partial<Kernel.IModel>,
      options?: DocumentRegistry.IOpenOptions
    ): IDocumentWidget | undefined => {
      const ref = options?.ref;
      if (ref === '_noref') {
        docOpen.call(docManager, path, widgetName, kernel, options);
        return;
      }
      const ext = PathExt.extname(path);
      let route = 'edit';
      if (
        (widgetName === 'default' && ext === '.ipynb') ||
        widgetName === 'Notebook'
      ) {
        route = 'notebooks';
      }
      let url = `${baseUrl}${route}/${path}`;
      // append ?factory only if it's not the default
      if (widgetName !== 'default') {
        url = `${url}?factory=${widgetName}`;
      }
      window.open(url);
      return undefined;
    };
  }
};

/**
 * Export the plugins as default.
 */
const plugins: JupyterFrontEndPlugin<any>[] = [opener];

export default plugins;
