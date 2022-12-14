// Copyright (c) Jupyter Development Team.
// Distributed under the terms of the Modified BSD License.

import {
  ILabStatus,
  IRouter,
  ITreePathUpdater,
  JupyterFrontEnd,
  JupyterFrontEndPlugin,
  Router
} from '@jupyterlab/application';

import {
  sessionContextDialogs,
  ISessionContextDialogs,
  DOMUtils,
  ICommandPalette,
  IToolbarWidgetRegistry
} from '@jupyterlab/apputils';

import { ConsolePanel } from '@jupyterlab/console';

import { PageConfig, PathExt, URLExt } from '@jupyterlab/coreutils';

import { IDocumentManager, renameDialog } from '@jupyterlab/docmanager';

import { DocumentWidget } from '@jupyterlab/docregistry';

import { IMainMenu } from '@jupyterlab/mainmenu';

import { ISettingRegistry } from '@jupyterlab/settingregistry';

import { ITranslator } from '@jupyterlab/translation';

import {
  NotebookApp,
  NotebookShell,
  INotebookShell
} from '@jupyter-notebook/application';

import { jupyterIcon } from '@jupyter-notebook/ui-components';

import { PromiseDelegate } from '@lumino/coreutils';

import { DisposableDelegate, DisposableSet } from '@lumino/disposable';

import { Widget } from '@lumino/widgets';

/**
 * A regular expression to match path to notebooks and documents
 */
const TREE_PATTERN = new RegExp('/(notebooks|edit)/(.*)');

/**
 * A regular expression to suppress the file extension from display for .ipynb files.
 */
const STRIP_IPYNB = /\.ipynb$/;

/**
 * The command IDs used by the application plugin.
 */
namespace CommandIDs {
  /**
   * Toggle Top Bar visibility
   */
  export const toggleTop = 'application:toggle-top';

  /**
   * Toggle the Zen mode
   */
  export const toggleZen = 'application:toggle-zen';

  /**
   * Open JupyterLab
   */
  export const openLab = 'application:open-lab';

  /**
   * Open the tree page.
   */
  export const openTree = 'application:open-tree';

  /**
   * Rename the current document
   */
  export const rename = 'application:rename';

  /**
   * Resolve tree path
   */
  export const resolveTree = 'application:resolve-tree';
}

/**
 * Check if the application is dirty before closing the browser tab.
 */
const dirty: JupyterFrontEndPlugin<void> = {
  id: '@jupyter-notebook/application-extension:dirty',
  autoStart: true,
  requires: [ILabStatus, ITranslator],
  activate: (
    app: JupyterFrontEnd,
    status: ILabStatus,
    translator: ITranslator
  ): void => {
    if (!(app instanceof NotebookApp)) {
      throw new Error(`${dirty.id} must be activated in Jupyter Notebook.`);
    }
    const trans = translator.load('notebook');
    const message = trans.__(
      'Are you sure you want to exit Jupyter Notebook?\n\nAny unsaved changes will be lost.'
    );

    window.addEventListener('beforeunload', event => {
      if (app.status.isDirty) {
        return ((event as any).returnValue = message);
      }
    });
  }
};

/**
 * The logo plugin.
 */
const logo: JupyterFrontEndPlugin<void> = {
  id: '@jupyter-notebook/application-extension:logo',
  autoStart: true,
  activate: (app: JupyterFrontEnd) => {
    const baseUrl = PageConfig.getBaseUrl();
    const node = document.createElement('a');
    node.href = `${baseUrl}tree`;
    node.target = '_blank';
    node.rel = 'noopener noreferrer';
    const logo = new Widget({ node });

    jupyterIcon.element({
      container: node,
      elementPosition: 'center',
      padding: '2px 2px 2px 8px',
      height: '28px',
      width: 'auto'
    });
    logo.id = 'jp-NotebookLogo';
    app.shell.add(logo, 'top', { rank: 0 });
  }
};

/**
 * A plugin to open documents in the main area.
 */
const opener: JupyterFrontEndPlugin<void> = {
  id: '@jupyter-notebook/application-extension:opener',
  autoStart: true,
  requires: [IRouter, IDocumentManager],
  activate: (
    app: JupyterFrontEnd,
    router: IRouter,
    docManager: IDocumentManager
  ): void => {
    const { commands } = app;

    const command = 'router:tree';
    commands.addCommand(command, {
      execute: (args: any) => {
        const parsed = args as IRouter.ILocation;
        const matches = parsed.path.match(TREE_PATTERN) ?? [];
        const [, , path] = matches;
        if (!path) {
          return;
        }

        const file = decodeURIComponent(path);
        const urlParams = new URLSearchParams(parsed.search);
        const factory = urlParams.get('factory') ?? 'default';
        app.restored.then(async () => {
          docManager.open(file, factory, undefined, {
            ref: '_noref'
          });
        });
      }
    });

    router.register({ command, pattern: TREE_PATTERN });
  }
};

/**
 * A plugin to customize menus
 *
 * TODO: use this plugin to customize the menu items and their order
 */
const menus: JupyterFrontEndPlugin<void> = {
  id: '@jupyter-notebook/application-extension:menus',
  requires: [IMainMenu],
  autoStart: true,
  activate: (app: JupyterFrontEnd, menu: IMainMenu) => {
    // always disable the Tabs menu
    menu.tabsMenu.dispose();

    const page = PageConfig.getOption('notebookPage');
    switch (page) {
      case 'consoles':
      case 'terminals':
      case 'tree':
        menu.editMenu.dispose();
        menu.kernelMenu.dispose();
        menu.runMenu.dispose();
        break;
      case 'edit':
        menu.kernelMenu.dispose();
        menu.runMenu.dispose();
        break;
      default:
        break;
    }
  }
};

/**
 * A plugin to provide a spacer at rank 900 in the menu area
 */
const menuSpacer: JupyterFrontEndPlugin<void> = {
  id: '@jupyter-notebook/application-extension:menu-spacer',
  autoStart: true,
  activate: (app: JupyterFrontEnd) => {
    const menu = new Widget();
    menu.id = DOMUtils.createDomID();
    menu.addClass('jp-NotebookSpacer');
    app.shell.add(menu, 'menu', { rank: 900 });
  }
};

/**
 * Add commands to open the tree and running pages.
 */
const pages: JupyterFrontEndPlugin<void> = {
  id: '@jupyter-notebook/application-extension:pages',
  autoStart: true,
  requires: [ITranslator],
  optional: [ICommandPalette],
  activate: (
    app: JupyterFrontEnd,
    translator: ITranslator,
    palette: ICommandPalette | null
  ): void => {
    const trans = translator.load('notebook');
    const baseUrl = PageConfig.getBaseUrl();

    app.commands.addCommand(CommandIDs.openLab, {
      label: trans.__('Open JupyterLab'),
      execute: () => {
        window.open(`${baseUrl}lab`);
      }
    });

    app.commands.addCommand(CommandIDs.openTree, {
      label: trans.__('Open Files'),
      execute: () => {
        window.open(`${baseUrl}tree`);
      }
    });

    if (palette) {
      [CommandIDs.openLab, CommandIDs.openTree].forEach(command => {
        palette.addItem({ command, category: 'View' });
      });
    }
  }
};

/**
 * The default paths for a Jupyter Notebook app.
 */
const paths: JupyterFrontEndPlugin<JupyterFrontEnd.IPaths> = {
  id: '@jupyter-notebook/application-extension:paths',
  autoStart: true,
  provides: JupyterFrontEnd.IPaths,
  activate: (app: JupyterFrontEnd): JupyterFrontEnd.IPaths => {
    if (!(app instanceof NotebookApp)) {
      throw new Error(`${paths.id} must be activated in Jupyter Notebook.`);
    }
    return app.paths;
  }
};

/**
 * The default URL router provider.
 */
const router: JupyterFrontEndPlugin<IRouter> = {
  id: '@jupyter-notebook/application-extension:router',
  autoStart: true,
  provides: IRouter,
  requires: [JupyterFrontEnd.IPaths],
  activate: (app: JupyterFrontEnd, paths: JupyterFrontEnd.IPaths) => {
    const { commands } = app;
    const base = paths.urls.base;
    const router = new Router({ base, commands });
    void app.started.then(() => {
      // Route the very first request on load.
      void router.route();

      // Route all pop state events.
      window.addEventListener('popstate', () => {
        void router.route();
      });
    });
    return router;
  }
};

/**
 * The default session dialogs plugin
 */
const sessionDialogs: JupyterFrontEndPlugin<ISessionContextDialogs> = {
  id: '@jupyter-notebook/application-extension:session-dialogs',
  provides: ISessionContextDialogs,
  autoStart: true,
  activate: () => sessionContextDialogs
};

/**
 * The default Jupyter Notebook application shell.
 */
const shell: JupyterFrontEndPlugin<INotebookShell> = {
  id: '@jupyter-notebook/application-extension:shell',
  activate: (app: JupyterFrontEnd) => {
    if (!(app.shell instanceof NotebookShell)) {
      throw new Error(`${shell.id} did not find a NotebookShell instance.`);
    }
    return app.shell;
  },
  autoStart: true,
  provides: INotebookShell
};

/**
 * The default JupyterLab application status provider.
 */
const status: JupyterFrontEndPlugin<ILabStatus> = {
  id: '@jupyter-notebook/application-extension:status',
  autoStart: true,
  provides: ILabStatus,
  activate: (app: JupyterFrontEnd) => {
    if (!(app instanceof NotebookApp)) {
      throw new Error(`${status.id} must be activated in Jupyter Notebook.`);
    }
    return app.status;
  }
};

/**
 * A plugin to display the document title in the browser tab title
 */
const tabTitle: JupyterFrontEndPlugin<void> = {
  id: '@jupyter-notebook/application-extension:tab-title',
  autoStart: true,
  requires: [INotebookShell],
  activate: (app: JupyterFrontEnd, shell: INotebookShell) => {
    const setTabTitle = () => {
      const current = shell.currentWidget;
      if (current instanceof ConsolePanel) {
        const update = () => {
          const title =
            current.sessionContext.path || current.sessionContext.name;
          const basename = PathExt.basename(title);
          // Strip the ".ipynb" suffix from filenames for display in tab titles.
          document.title = basename.replace(STRIP_IPYNB, '');
        };
        current.sessionContext.sessionChanged.connect(update);
        update();
        return;
      } else if (current instanceof DocumentWidget) {
        const update = () => {
          const basename = PathExt.basename(current.context.path);
          document.title = basename.replace(STRIP_IPYNB, '');
        };
        current.context.pathChanged.connect(update);
        update();
      }
    };

    shell.currentChanged.connect(setTabTitle);
    setTabTitle();
  }
};

/**
 * A plugin to display and rename the title of a file
 */
const title: JupyterFrontEndPlugin<void> = {
  id: '@jupyter-notebook/application-extension:title',
  autoStart: true,
  requires: [INotebookShell, ITranslator],
  optional: [IDocumentManager, IRouter, IToolbarWidgetRegistry],
  activate: (
    app: JupyterFrontEnd,
    shell: INotebookShell,
    translator: ITranslator,
    docManager: IDocumentManager | null,
    router: IRouter | null,
    toolbarRegistry: IToolbarWidgetRegistry | null
  ) => {
    const { commands } = app;
    const trans = translator.load('notebook');

    const node = document.createElement('div');
    if (toolbarRegistry) {
      toolbarRegistry.addFactory('TopBar', 'widgetTitle', toolbar => {
        const widget = new Widget({ node });
        widget.id = 'jp-title';
        return widget;
      });
    }

    const addTitle = async (): Promise<void> => {
      const current = shell.currentWidget;
      if (!current || !(current instanceof DocumentWidget)) {
        return;
      }
      if (node.children.length > 0) {
        return;
      }

      const h = document.createElement('h1');
      h.textContent = current.title.label.replace(STRIP_IPYNB, '');
      node.appendChild(h);
      node.style.marginLeft = '10px';
      if (!docManager) {
        return;
      }

      const isEnabled = () => {
        const { currentWidget } = shell;
        return !!(currentWidget && docManager.contextForWidget(currentWidget));
      };

      commands.addCommand(CommandIDs.rename, {
        label: () => trans.__('Rename…'),
        isEnabled,
        execute: async () => {
          if (!isEnabled()) {
            return;
          }

          const result = await renameDialog(docManager, current.context.path);

          // activate the current widget to bring the focus
          if (current) {
            current.activate();
          }

          if (result === null) {
            return;
          }

          const newPath = current.context.path ?? result.path;
          const basename = PathExt.basename(newPath);

          h.textContent = basename.replace(STRIP_IPYNB, '');
          if (!router) {
            return;
          }
          const matches = router.current.path.match(TREE_PATTERN) ?? [];
          const [, route, path] = matches;
          if (!route || !path) {
            return;
          }
          const encoded = encodeURIComponent(newPath);
          router.navigate(`/${route}/${encoded}`, {
            skipRouting: true
          });
        }
      });

      node.onclick = async () => {
        void commands.execute(CommandIDs.rename);
      };
    };

    shell.currentChanged.connect(addTitle);
    void addTitle();
  }
};

/**
 * Plugin to toggle the top header visibility.
 */
const topVisibility: JupyterFrontEndPlugin<void> = {
  id: '@jupyter-notebook/application-extension:top',
  requires: [INotebookShell, ITranslator],
  optional: [ISettingRegistry, ICommandPalette],
  activate: (
    app: JupyterFrontEnd<JupyterFrontEnd.IShell>,
    notebookShell: INotebookShell,
    translator: ITranslator,
    settingRegistry: ISettingRegistry | null,
    palette: ICommandPalette | null
  ) => {
    const trans = translator.load('notebook');
    const top = notebookShell.top;
    const pluginId = topVisibility.id;

    app.commands.addCommand(CommandIDs.toggleTop, {
      label: trans.__('Show Header'),
      execute: () => {
        top.setHidden(top.isVisible);
        if (settingRegistry) {
          void settingRegistry.set(pluginId, 'visible', top.isVisible);
        }
      },
      isToggled: () => top.isVisible
    });

    let settingsOverride = false;

    if (settingRegistry) {
      const loadSettings = settingRegistry.load(pluginId);
      const updateSettings = (settings: ISettingRegistry.ISettings): void => {
        const visible = settings.get('visible').composite;
        if (settings.user.visible !== undefined) {
          settingsOverride = true;
          top.setHidden(!visible);
        }
      };

      Promise.all([loadSettings, app.restored])
        .then(([settings]) => {
          updateSettings(settings);
          settings.changed.connect(settings => {
            updateSettings(settings);
          });
        })
        .catch((reason: Error) => {
          console.error(reason.message);
        });
    }

    if (palette) {
      palette.addItem({ command: CommandIDs.toggleTop, category: 'View' });
    }

    const onChanged = (): void => {
      if (settingsOverride) {
        return;
      }
      if (app.format === 'desktop') {
        notebookShell.expandTop();
      } else {
        notebookShell.collapseTop();
      }
    };

    // listen on format change (mobile and desktop) to make the view more compact
    app.formatChanged.connect(onChanged);
  },
  autoStart: true
};

/**
 * The default tree route resolver plugin.
 */
const tree: JupyterFrontEndPlugin<JupyterFrontEnd.ITreeResolver> = {
  id: '@jupyter-notebook/application-extension:tree-resolver',
  autoStart: true,
  requires: [IRouter],
  provides: JupyterFrontEnd.ITreeResolver,
  activate: (
    app: JupyterFrontEnd,
    router: IRouter
  ): JupyterFrontEnd.ITreeResolver => {
    const { commands } = app;
    const set = new DisposableSet();
    const delegate = new PromiseDelegate<JupyterFrontEnd.ITreeResolver.Paths>();

    const treePattern = new RegExp('/(/tree/.*)?');

    set.add(
      commands.addCommand(CommandIDs.resolveTree, {
        execute: (async (args: IRouter.ILocation) => {
          if (set.isDisposed) {
            return;
          }

          const query = URLExt.queryStringToObject(args.search ?? '');
          const browser = query['file-browser-path'] || '';

          // Remove the file browser path from the query string.
          delete query['file-browser-path'];

          // Clean up artifacts immediately upon routing.
          set.dispose();

          delegate.resolve({ browser, file: PageConfig.getOption('treePath') });
        }) as (args: any) => Promise<void>
      })
    );
    set.add(
      router.register({ command: CommandIDs.resolveTree, pattern: treePattern })
    );

    // If a route is handled by the router without the tree command being
    // invoked, resolve to `null` and clean up artifacts.
    const listener = () => {
      if (set.isDisposed) {
        return;
      }
      set.dispose();
      delegate.resolve(null);
    };
    router.routed.connect(listener);
    set.add(
      new DisposableDelegate(() => {
        router.routed.disconnect(listener);
      })
    );

    return { paths: delegate.promise };
  }
};

const treePathUpdater: JupyterFrontEndPlugin<ITreePathUpdater> = {
  id: '@jupyter-notebook/application-extension:tree-updater',
  requires: [IRouter],
  provides: ITreePathUpdater,
  activate: (app: JupyterFrontEnd, router: IRouter) => {
    function updateTreePath(treePath: string) {
      if (treePath !== PageConfig.getOption('treePath')) {
        const path = URLExt.join(
          PageConfig.getOption('baseUrl') || '/',
          'tree',
          URLExt.encodeParts(treePath)
        );
        router.navigate(path, { skipRouting: true });
        // Persist the new tree path to PageConfig as it is used elsewhere at runtime.
        PageConfig.setOption('treePath', treePath);
      }
    }
    return updateTreePath;
  },
  autoStart: true
};

/**
 * Zen mode plugin
 */
const zen: JupyterFrontEndPlugin<void> = {
  id: '@jupyter-notebook/application-extension:zen',
  autoStart: true,
  requires: [ITranslator],
  optional: [ICommandPalette, INotebookShell],
  activate: (
    app: JupyterFrontEnd,
    translator: ITranslator,
    palette: ICommandPalette | null,
    notebookShell: INotebookShell | null
  ): void => {
    const { commands } = app;
    const elem = document.documentElement;
    const trans = translator.load('notebook');

    const toggleOn = () => {
      notebookShell?.collapseTop();
      notebookShell?.menu.setHidden(true);
      zenModeEnabled = true;
    };

    const toggleOff = () => {
      notebookShell?.expandTop();
      notebookShell?.menu.setHidden(false);
      zenModeEnabled = false;
    };

    let zenModeEnabled = false;
    commands.addCommand(CommandIDs.toggleZen, {
      label: trans.__('Toggle Zen Mode'),
      execute: () => {
        if (!zenModeEnabled) {
          elem.requestFullscreen();
          toggleOn();
        } else {
          document.exitFullscreen();
          toggleOff();
        }
      }
    });

    document.addEventListener('fullscreenchange', () => {
      if (!document.fullscreenElement) {
        toggleOff();
      }
    });

    if (palette) {
      palette.addItem({ command: CommandIDs.toggleZen, category: 'Mode' });
    }
  }
};

/**
 * Export the plugins as default.
 */
const plugins: JupyterFrontEndPlugin<any>[] = [
  dirty,
  logo,
  menus,
  menuSpacer,
  opener,
  pages,
  paths,
  router,
  sessionDialogs,
  shell,
  status,
  tabTitle,
  title,
  topVisibility,
  tree,
  treePathUpdater,
  zen
];

export default plugins;
